# 03. Copy and Move

C++ 객체의 복사와 이동이 언제 호출되는지, 객체의 identity와 소유 자원이 어떻게 달라지는지 정리한 학습 기록이다.

## 1. 복사 생성과 복사 대입

### 질문

다음 두 코드는 모두 `=`를 사용한다. 같은 동작일까?

```cpp
CopyTracer copied = original;
copied = original;
```

### 정리

첫 번째 코드는 새 객체를 만드는 복사 생성이고, 두 번째 코드는 이미 존재하는 객체의 값을 바꾸는 복사 대입이다.

```text
CopyTracer copied = original; -> 복사 생성자
copied = original;            -> 복사 대입 연산자
```

복사 대입 후에도 왼쪽 객체의 identity와 주소는 유지되고 내부 값만 바뀐다.

```cpp
CopyTracer& operator=(const CopyTracer& other)
{
    Name = other.Name;
    return *this;
}
```

`return *this`는 대입의 왼쪽 객체를 참조로 반환한다. 덕분에 `first = second = third`와 같은 연쇄 대입이 가능하다.

## 2. 컴파일러가 만드는 기본 복사 연산

복사 생성자나 복사 대입 연산자를 직접 구현하지 않아도 조건이 맞으면 컴파일러가 멤버별 복사를 제공한다.

```cpp
CopyTracer(const CopyTracer&) = default;
CopyTracer& operator=(const CopyTracer&) = default;
```

복사를 금지하려면 명시적으로 삭제한다.

```cpp
CopyTracer(const CopyTracer&) = delete;
CopyTracer& operator=(const CopyTracer&) = delete;
```

`std::string`과 `std::vector`처럼 자원을 스스로 관리하는 멤버만 있다면 특별 멤버 함수를 직접 작성하지 않는 Rule of Zero가 가장 자연스럽다.

## 3. lvalue와 rvalue

### 질문

lvalue와 rvalue는 설명을 위한 용어인가, 컴파일러가 실제로 구분하는 언어 개념인가?

### 정리

lvalue와 rvalue는 C++ 언어에 정의된 표현식의 value category다. 컴파일러는 타입과 value category를 이용해 참조 바인딩과 overload resolution을 수행한다.

```cpp
CopyTracer tracer{"Tracer"};

tracer;            // lvalue
std::move(tracer); // xvalue, rvalue
```

```text
T&       -> lvalue reference
const T& -> lvalue와 rvalue 모두 받을 수 있음
T&&      -> rvalue reference
```

비템플릿 코드에서 `CopyTracer&&`는 rvalue만 받는 rvalue reference다. `&&`는 참조의 참조가 아니라 별도의 언어 문법이다.

## 4. std::move의 의미

`std::move`는 객체를 직접 이동시키지 않는다. lvalue 표현식을 이동 가능한 rvalue로 변환한다.

```cpp
CopyTracer moved{std::move(source)};
```

실제 자원 이동은 선택된 이동 생성자 또는 이동 대입 연산자가 수행한다.

이동 함수의 매개변수 `other`는 타입이 `T&&`여도 이름을 가진 표현식이므로 함수 내부에서는 lvalue다. 따라서 멤버를 이동할 때 다시 `std::move`가 필요하다.

```cpp
CopyTracer(CopyTracer&& other) noexcept
    : Name{std::move(other.Name)}
{
}
```

## 5. 이동 생성과 이동 대입

```text
T moved{std::move(source)}; -> 새 객체 생성, 이동 생성자
target = std::move(source); -> 기존 객체 변경, 이동 대입 연산자
```

이동 생성자는 아직 존재하지 않는 멤버를 생성하므로 멤버 초기화 목록을 사용한다.

```cpp
CopyTracer(CopyTracer&& other) noexcept
    : Name{std::move(other.Name)}
{
}
```

이동 대입 시에는 대상 멤버가 이미 존재하므로 함수 본문에서 대입한다.

```cpp
CopyTracer& operator=(CopyTracer&& other) noexcept
{
    Name = std::move(other.Name);
    return *this;
}
```

## 6. 이동 대입과 기존 target 자원

### 질문

`target.Name`이 이미 heap 자원을 소유하고 있는데 `source.Name`의 자원을 이동 대입하면 기존 target 자원은 누수되지 않는가?

### 처음 이해한 위험

```text
target.Name -> heap A
source.Name -> heap B
```

단순히 target이 heap B의 주소를 받으면 heap A의 주소를 잃어 메모리 누수가 발생할 수 있다고 생각했다.

### 정리

그 위험은 raw pointer를 단순 대입할 때 실제로 발생한다. 하지만 `std::string`의 이동 대입 연산자는 기존 target 자원을 먼저 해제하거나 재사용한 뒤 source의 자원을 넘겨받는다.

```text
이동 전
target.Name -> heap A: "Target"
source.Name -> heap B: "Source"

이동 대입
1. target.Name이 heap A를 정리하거나 재사용
2. source.Name의 heap B 소유권을 target.Name으로 이전
3. source.Name은 유효하지만 unspecified state

이동 후
target.Name -> heap B: "Source"
source.Name -> 유효하지만 값은 미지정
```

이때 `target.Name`이라는 `std::string` 객체 자체의 소멸자가 호출되는 것은 아니다. 살아 있는 `std::string` 객체의 이동 대입 연산자가 내부 자원을 교체한다. `target`이 나중에 파괴될 때 `Name`의 소멸자가 한 번 호출된다.

raw pointer는 자원 정리 책임을 제공하지 않는다.

```cpp
target.Data = other.Data; // 기존 target.Data가 소유한 자원을 잃을 수 있음
```

`std::string`, `std::vector`, `std::unique_ptr` 같은 RAII 타입은 이동 대입 과정에서 기존 자원을 안전하게 처리한다.

## 7. 이동된 객체의 상태

이동된 원본 객체는 파괴하거나 새 값을 대입할 수 있는 유효한 상태다. 다만 구체적인 값은 unspecified state다.

```cpp
CopyTracer moved{std::move(source)};

// source는 파괴 가능하고 재대입 가능하다.
// source.Name이 반드시 빈 문자열이라고 가정하면 안 된다.
```

현재 MSVC에서 빈 문자열로 보이더라도 구현 결과에 의존하지 않는다.

## 8. noexcept 이동

`noexcept`는 함수 실행 조건이 아니라 예외를 함수 밖으로 내보내지 않겠다는 약속이다.

```cpp
CopyTracer(CopyTracer&& other) noexcept;
CopyTracer& operator=(CopyTracer&& other) noexcept;
```

`noexcept` 함수에서 예외가 밖으로 빠져나오면 `std::terminate()`가 호출된다.

`std::vector` 같은 컨테이너는 재할당 중 상태를 안전하게 유지하기 위해 `noexcept` 이동을 선호한다. 이동이 예외를 던질 수 있고 복사가 가능하면 복사를 선택할 수 있다.

## 핵심 요약

```text
복사 생성     -> 새 객체를 원본 값으로 생성
복사 대입     -> 기존 객체의 주소를 유지하며 값을 복사
이동 생성     -> 새 객체가 원본의 자원을 넘겨받음
이동 대입     -> 기존 target 자원을 정리하고 원본 자원을 넘겨받음
std::move     -> 이동 실행이 아니라 rvalue 변환
이동된 원본   -> 유효하지만 값은 unspecified
noexcept 이동 -> 컨테이너가 안전하게 이동을 선택할 근거
RAII 멤버     -> 기존 자원 정리와 ownership 이전을 타입이 담당
raw pointer   -> 이동처럼 대입해도 주소 복사일 뿐, 자동 자원 정리 없음
```

복사와 이동을 직접 구현하는 실습은 특별 멤버 함수의 호출 시점을 확인하기 위한 것이다. 실제 코드에서는 자원 관리 타입을 멤버로 사용하고 Rule of Zero를 우선한다.
