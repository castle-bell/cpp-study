# 03. Copy and Move

C++ 객체의 복사·이동과 자원 소유권을 실습한 기록이다.

## 복사 생성과 복사 대입

```cpp
IntBuffer copied{original}; // 복사 생성

IntBuffer target{5};
target = original;          // 복사 대입
```

- 복사 생성은 새 객체를 만들며 원본의 값을 복사한다.
- 복사 대입은 이미 존재하는 target의 상태를 바꾼다.
- 대입 후에도 target 객체 자체의 주소와 identity는 그대로다.
- `operator=`는 연쇄 대입을 지원하도록 일반적으로 `*this`를 참조로 반환한다.

raw pointer가 동적 배열을 소유하는 경우 포인터 값만 복사하면 두 객체가 같은 배열을 가리킨다. 그러면 한쪽이 자원을 삭제했을 때 다른 포인터가 dangling pointer가 되고, 두 소멸자가 같은 자원을 삭제하면 double delete가 발생한다. 따라서 서로 다른 배열을 갖도록 깊은 복사가 필요하다.

## 복사 대입과 예외 안전성

기존 자원을 먼저 삭제한 뒤 `new`를 하면, 메모리 할당 실패 시 target이 깨진 상태로 남을 수 있다.

안전한 순서는 다음과 같다.

1. 새 자원을 준비한다.
2. 새 자원에 원본 내용을 복사한다.
3. 준비가 모두 성공한 후 target의 기존 자원을 정리한다.
4. target이 새 자원을 소유하게 한다.

`IntBuffer`의 원소는 `int`이므로 원소 대입은 예외를 던지지 않지만, `new` 자체는 실패할 수 있다.

## lvalue, rvalue, std::move

- lvalue와 rvalue는 C++ 언어가 실제로 구분하는 expression value category다.
- `T&`는 lvalue reference이다.
- `const T&`는 lvalue와 rvalue 둘 다 받을 수 있다.
- `T&&`는 rvalue reference이다.
- 이름이 있는 rvalue reference 변수는 표현식으로 사용하면 lvalue다.
- `std::move` 자체가 자원을 옮기는 것은 아니다. 대상을 이동 가능한 value category로 변환하는 cast에 가깝다.
- 실제 소유권 이전은 이동 생성자나 이동 대입 연산자가 수행한다.

## 이동 생성과 이동 대입

```cpp
IntBuffer moved{std::move(source)}; // 이동 생성
target = std::move(source);         // 이동 대입
```

이동 생성자의 target은 아직 자원을 소유하지 않는 새 객체다. source의 크기와 포인터를 가져온 뒤 source를 `0`, `nullptr` 상태로 만들면 된다.

이동 대입의 target은 이미 자원을 소유할 수 있으므로 기존 자원도 정리해야 한다. 자기 이동 대입인 `buffer = std::move(buffer)`도 유효한 상태로 남도록 처리했다.

일반적인 moved-from 객체는 파괴하거나 새 값을 대입할 수 있는 valid but unspecified state에 남는다. 따라서 타입이 별도로 보장하지 않는 한 특정한 값을 가정하면 안 된다. 실습의 `IntBuffer`는 이동 후 `Size == 0`, `Data == nullptr`로 직접 설정했으므로, 이 타입은 자체 규약으로 빈 상태를 명시적으로 보장한다.

## noexcept

`noexcept`는 예외가 없을 때만 함수를 실행한다는 뜻이 아니다. 함수 밖으로 예외와 같은 비정상 탈출이 발생하지 않는다고 약속하는 것이다. 약속을 어겨 예외가 빠져나오면 `std::terminate` 종료 로직이 실행될 수 있다.

`IntBuffer`의 이동은 크기와 포인터만 대입하며 새로운 할당이 없으므로 `noexcept`가 적절하다. `std::vector`와 같은 표준 컨테이너는 재할당 중 안전성을 유지하기 위해 `noexcept` 이동을 선호할 수 있다.

## Rule of Zero, Three, Five

이 세 규칙은 컴파일러가 강제하는 문법 규칙이 아니라, special member function과 자원 소유권을 안전하게 설계하기 위한 지침이다.

### 내가 이해한 Rule of Zero

> 이미 소유권과 자원 정리가 잘 정의된 라이브러리 클래스만 멤버로 사용한다면 special member function을 직접 구현하지 않는 것이 좋다.

```cpp
class IntBuffer
{
private:
    std::vector<int> Data;
};
```

`std::vector` 자체가 소멸·복사·이동을 올바르게 구현하므로 `IntBuffer`는 그 동작을 조합해 사용하면 된다. 현대 C++에서 가장 선호하는 방식이다.

### 내가 이해한 Rule of Three

> raw pointer 등을 통해 자원을 직접 소유해 소멸자에서 정리해야 한다면, 복사를 지원할 경우 복사 생성자와 복사 대입 연산자도 함께 올바르게 구현해야 자원 관리 문제가 없다. 복사하면 안 되는 타입이라면 두 복사 함수를 `= delete`로 금지해야 한다.

핵심은 “소멸자를 작성했다” 자체보다, 소멸자가 필요할 정도의 자원 소유 책임을 클래스가 갖고 있다는 점이다.

Rule of Three의 세 함수:

1. 소멸자
2. 복사 생성자
3. 복사 대입 연산자

### 내가 이해한 Rule of Five

> 자원 소유 클래스가 이동까지 지원해야 한다면 이동 생성자와 이동 대입 연산자도 추가로 구현한다.

Rule of Five의 다섯 함수:

1. 소멸자
2. 복사 생성자
3. 복사 대입 연산자
4. 이동 생성자
5. 이동 대입 연산자

이동을 반드시 지원해야 하는 것은 아니다. 클래스 의도에 따라 복사나 이동을 `= delete`로 금지할 수도 있다. 중요한 것은 컴파일러의 멤버별 얕은 복사와 자동 생성 규칙에 무심하게 의존하지 않고, 클래스의 소유권 의도를 명확하게 만드는 것이다.

## 결론

- 실습에서는 raw pointer의 소유권을 직접 관리해 Rule of Three/Five가 필요한 이유를 확인했다.
- 실제 코드에서는 `std::vector`, `std::string`, `std::unique_ptr` 같은 RAII 타입을 멤버로 사용해 Rule of Zero를 선호한다.
- 소유권을 직접 관리해야 한다면 복사·이동·파괴 전체를 하나의 설계로 바라봐야 한다.
