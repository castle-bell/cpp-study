# STL: 알고리즘과 컨테이너 검색

## 범용 알고리즘

`std::find`, `std::sort` 같은 표준 알고리즘은 특정 컨테이너의 멤버 함수가 아니라, 보통 iterator 범위 `[begin, end)`를 받는다.

```cpp
std::find(levels.begin(), levels.end(), 10);
std::sort(levels.begin(), levels.end());
```

그래서 `std::vector`뿐 아니라 iterator를 제공하는 여러 컨테이너에 같은 알고리즘을 재사용할 수 있다. 이것은 iterator가 **정렬되어 있다**는 뜻이 아니라, 컨테이너의 순회 범위를 표현한다는 뜻이다.

## unordered_map의 키 검색

`std::unordered_map`의 원소는 값 하나가 아니라 `pair<const Key, Value>` 형태의 키-값 쌍이다.

```cpp
std::unordered_map<std::string, int> monsterHps{
    {"Slime", 100},
    {"Orc", 250},
};
```

키로 원소를 찾을 때는 범용 `std::find`보다 컨테이너의 멤버 함수 `find()`를 쓴다.

```cpp
const auto found = monsterHps.find("Orc");

if (found != monsterHps.end())
{
    std::cout << found->second << '\n';
}
```

- `found->first`: 키 (`"Orc"`)
- `found->second`: 값 (`250`)

`unordered_map::find(key)`는 키의 해시를 사용해 평균적으로 빠르게 찾는다. `std::find`도 unordered_map의 iterator 범위에서 사용할 수는 있지만, 모든 원소를 순회하고 pair 전체를 비교해야 하므로 키 검색 용도로는 적절하지 않다.

## 기억할 기준

- 순차 컨테이너에서 값 검색·정렬: `std::find`, `std::sort` 같은 범용 알고리즘
- 키-값 컨테이너에서 키 검색: `map.find(key)`, `unordered_map.find(key)` 같은 멤버 함수
