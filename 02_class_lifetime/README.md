# 02. Class Lifetime

C++ 객체가 언제 생성되고 파괴되는지, 참조와 포인터가 객체의 수명에 어떤 영향을 주는지 정리한 학습 기록이다.

이 문서는 학습 중 받은 질문, 처음 생각한 답, 교정된 내용을 순서대로 기록한다.

## 1. 지역 객체와 scope

### 질문

지역 객체에 `delete`를 호출하지 않아도 scope가 끝날 때 소멸자가 호출되는 이유는 무엇인가?

```cpp
{
    LifetimeTracer tracer{};
}
```

### 내 답

지역 객체이므로 scope가 끝날 때 자동으로 파괴되는 것으로 이해했다.

### 정리

`tracer`는 automatic storage duration을 가진 지역 객체다. 생성된 scope를 벗어날 때 소멸자가 자동으로 호출된다.

```text
Constructed
Destroyed
```

`new`로 생성한 객체가 아니므로 `delete`는 필요하지 않다.

## 2. 멤버 객체의 생성과 파괴

### 질문

`Player`가 `Equipment` 객체를 멤버로 가지고 있다면 생성자와 소멸자는 어떤 순서로 실행되는가?

### 내 답

```text
Player 생성
Equipment 생성
Equipment 파괴
Player 파괴
```

### 교정

실제 순서는 다음과 같다.

```text
Equipment 생성
Player 생성자 본문
Player 소멸자 본문
Equipment 파괴
```

`Player` 생성자 본문에 진입했을 때는 모든 멤버가 이미 사용 가능한 상태여야 한다. 파괴는 생성의 반대 순서로 진행된다.

```text
생성: 멤버 객체 -> 소유 객체의 생성자 본문
파괴: 소유 객체의 소멸자 본문 -> 멤버 객체
```

## 3. 지역 객체의 참조 반환

### 질문

다음 함수가 반환한 참조는 안전한가?

```cpp
const std::string& CreateName()
{
    std::string name{"Player"};
    return name;
}
```

### 내 답

처음에는 `name`이 `main()` 종료 시점에 파괴될 것으로 생각했다. 파괴된다면 반환된 참조가 dangling reference가 될 것이라고 예상했지만, 안전한 수정 방법은 알지 못했다.

### 교정

지역 객체 `name`은 `main()`이 아니라 `CreateName()`이 끝나는 순간 파괴된다. 참조는 객체를 소유하거나 수명을 연장하지 않으므로 반환된 참조는 즉시 dangling reference가 된다.

안전하게 소유권을 전달하려면 값으로 반환한다.

```cpp
std::string CreateName()
{
    std::string name{"Player"};
    return name;
}
```

## 4. 값 반환과 NRVO

### 질문

지역 객체를 값으로 반환하면 객체가 파괴되기 직전에 복사해서 반환하는 것인가?

### 정리

최적화가 없다면 반환 객체를 복사 또는 이동으로 먼저 생성한 뒤 지역 객체를 파괴한다. 반환 객체는 지역 객체와 별개이므로 안전하다.

```text
지역 객체 생성
반환 객체 생성
지역 객체 파괴
호출자가 반환 객체 사용
```

NRVO는 Named Return Value Optimization의 약자다. 이름 있는 지역 객체를 반환할 때 컴파일러가 호출자의 결과 저장 공간에 객체를 직접 생성할 수 있다.

```cpp
std::string CreateName()
{
    std::string name{"Player"};
    return name; // NRVO 후보
}
```

NRVO가 적용되면 복사와 이동이 모두 생략된다. 적용되지 않아도 일반적으로 이동이 시도된다.

지역 값 반환에는 불필요한 `std::move`를 붙이지 않는다. `return std::move(name);`은 NRVO를 방해할 수 있다.

## 5. 임시 객체와 const reference

### 질문

다음 참조는 첫 줄이 끝난 뒤 dangling reference가 되는가?

```cpp
const std::string& name = std::string{"Player"};
```

### 내 답

안전하고 임시 객체는 `main()` 종료 시 파괴될 것으로 예상했다. 하지만 `const` reference가 lifetime에 영향을 주지는 않으며, 일반 `std::string&`로도 받을 수 있을 것으로 생각했다.

### 교정

임시 객체가 `const T&`에 직접 바인딩되면 임시 객체의 lifetime이 해당 참조의 lifetime까지 연장된다.

```cpp
const std::string& name = std::string{"Player"}; // 안전
std::string& other = std::string{"Player"};     // 컴파일 오류
```

non-const lvalue reference는 rvalue인 임시 객체에 바인딩할 수 없다.

lifetime 연장은 다른 참조를 거쳐 전달되지 않는다.

```cpp
const std::string& PassThrough(const std::string& value)
{
    return value;
}

const std::string& name = PassThrough(std::string{"Player"}); // dangling
```

## 6. lvalue와 rvalue

### 질문

lvalue와 rvalue는 무엇이며 이름은 어디에서 왔는가?

### 정리

- lvalue: left value에서 유래했다. 정체성과 저장 위치가 있어 다시 접근할 수 있는 객체를 가리키는 표현이다.
- rvalue: right value에서 유래했다. 임시 값이나 자원을 이동시킬 수 있는 만료 예정 값을 나타내는 표현이다.

```cpp
int level{10};

level; // lvalue
10;    // rvalue
```

참조 타입과의 기본 관계는 다음과 같다.

```text
T&       -> 주로 lvalue에 바인딩
const T& -> lvalue와 rvalue 모두에 바인딩 가능
T&&      -> rvalue에 바인딩
```

`std::move`는 객체를 직접 이동시키지 않는다. 표현식을 rvalue로 취급하도록 변환하며, 실제 이동은 이동 생성자나 이동 대입 연산자가 수행한다.

## 7. 함수 지역 static 객체

### 질문

다음 함수가 두 번 호출되면 객체는 몇 번 생성되고 언제 파괴되는가?

```cpp
LifetimeTracer& GetTracer()
{
    static LifetimeTracer tracer{};
    return tracer;
}
```

### 내 답

객체는 한 번만 생성되며 두 번째 호출도 첫 번째 호출에서 생성된 객체를 가리킬 것으로 예상했다.

### 보완

예상은 맞다. 함수 지역 `static` 객체는 선언에 처음 도달했을 때 한 번만 생성된다. 함수가 다시 호출되면 같은 객체의 참조를 반환한다.

객체는 함수 종료 시 파괴되지 않고 프로그램 종료 과정에서 파괴된다. 함수가 한 번도 호출되지 않으면 객체도 생성되지 않는다. C++11부터 최초 초기화는 thread-safe하게 한 번만 수행된다.

## 8. new로 생성한 객체의 lifetime

### 질문

다음 함수가 종료될 때 포인터와 객체는 각각 어떻게 되는가?

```cpp
void CreateTracer()
{
    LifetimeTracer* tracer = new LifetimeTracer{};
}
```

### 내 답

`LifetimeTracer` 소멸자는 호출되지 않고 메모리 누수가 발생한다고 판단했다. 포인터 변수는 `main()` 종료 시 사라질 것으로 생각했다.

### 교정

지역 포인터 변수 `tracer`는 `CreateTracer()`가 끝날 때 사라진다. `new`로 만든 동적 객체는 자동으로 파괴되지 않는다.

```text
동적 객체 생성
주소를 지역 포인터에 저장
함수 종료
지역 포인터 소멸
동적 객체는 남아 있지만 주소를 잃음
메모리 누수
```

직접 관리한다면 `delete`가 소멸자를 호출하고 메모리를 해제한다.

```cpp
delete tracer;
```

현대 C++ 실무에서는 소유권을 가진 raw `new/delete`를 직접 사용하는 대신 RAII와 `std::unique_ptr`를 우선한다. 여기서 raw pointer를 사용한 이유는 lifetime 원리를 관찰하기 위해서다.

## 9. delete 이후 포인터

### 질문

`delete tracer`를 실행하면 `tracer`가 자동으로 `nullptr`이 되는가?

### 내 답

자동으로 `nullptr`이 되므로 `tracer != nullptr` 조건이 거짓일 것으로 예상했다. 해제된 객체에 접근하면 문제가 생긴다는 점은 알고 있었다.

### 교정

`delete`는 포인터 변수의 값을 자동으로 `nullptr`로 바꾸지 않는다. 포인터에는 해제된 메모리 주소가 남아 dangling pointer가 된다.

```cpp
delete tracer;
tracer = nullptr; // 필요하다면 직접 변경
```

dangling pointer를 역참조하면 use-after-free이며 undefined behavior다. 반드시 즉시 충돌하는 것도 아니므로 더 위험하다.

## 10. 포인터 복사와 double delete

### 질문

다음 코드에서 `first`를 null로 바꾸면 `second`도 null이 되는가?

```cpp
LifetimeTracer* first = new LifetimeTracer{};
LifetimeTracer* second = first;

delete first;
first = nullptr;
```

### 내 답

`first`와 `second`는 서로 다른 위치에 존재하는 포인터 변수이고 저장된 주소값만 같으므로 `second`는 바뀌지 않는다고 판단했다. `second`를 다시 삭제하면 double free 문제가 생길 것으로 예상했다.

### 정리

예상은 맞다. `second`는 해제된 객체의 예전 주소를 가진 dangling pointer다.

```cpp
second->Print(); // use-after-free, undefined behavior
delete second;   // double delete, undefined behavior
```

한 포인터를 `nullptr`로 바꾸는 것은 다른 포인터 별칭에 영향을 주지 않는다. 이 문제를 해결하려면 누가 객체를 소유하고 누가 관찰만 하는지 명확히 해야 한다.

## 핵심 요약

```text
지역 객체              -> scope 종료 시 자동 파괴
멤버 객체              -> 소유 객체보다 먼저 생성되고 나중에 파괴
지역 객체의 참조 반환   -> dangling reference
값 반환                -> 안전하며 NRVO 또는 이동 최적화 가능
임시 객체 + const T&   -> 직접 바인딩하면 lifetime 연장
함수 지역 static       -> 최초 호출 시 생성, 프로그램 종료 시 파괴
new 객체               -> delete 전까지 자동 파괴되지 않음
delete 후 raw pointer  -> 자동으로 nullptr이 되지 않음
복사된 raw pointer      -> 한 포인터를 null로 만들어도 다른 별칭은 dangling
```

객체 lifetime과 ownership을 코드 구조로 관리하는 것이 RAII이며, 이후 `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr` 학습으로 이어진다.
