# Gameplay Framework Notes

## 핵심 역할

| 타입 | 책임 | 일반적인 lifetime |
| --- | --- | --- |
| `PlayerController` | 플레이어 입력을 해석하고 Pawn/Character를 조종한다. | Character가 죽어도 유지된다. |
| `PlayerState` | 플레이어 이름, 팀, 점수처럼 플레이어를 나타내는 데이터를 보관한다. | Character가 교체되어도 보통 유지된다. |
| `Pawn` / `Character` | 월드 안에서 조종되는 현재 몸체다. 위치, 이동, 체력 같은 상태를 가진다. | 사망·리스폰 시 파괴되고 새로 생성될 수 있다. |
| `Component` | Character/Actor에 붙는 기능 단위다. 예: 이동, 체력, 인벤토리, 상호작용. | 소유한 Actor/Character와 함께 정리되는 것이 자연스럽다. |
| `GameMode` | 스폰, 리스폰, 승패, 게임 오버 같은 월드 전체 규칙을 결정한다. | 현재 게임 규칙이 유효한 동안 유지된다. |
| `GameState` | 라운드 시간, 게임 진행 여부, 팀 점수처럼 현재 게임의 공유 상태를 보관한다. | 현재 맵/게임 진행 단위에 가깝다. |
| `GameInstance` | 설정값처럼 맵 전환 뒤에도 유지할 게임 실행 단위 상태를 보관한다. | 게임 프로그램 실행 동안 유지된다. |

## 플레이어와 몸체의 분리

`PlayerController`와 `PlayerState`는 한 명의 사용자/플레이어를 나타내고, `Character`는 그 플레이어가 현재 조종하는 월드 안의 몸체다.

```text
PlayerController ──Possess──> Character A
Character A 사망·파괴
PlayerController ──Possess──> Character B
```

따라서 Character의 HP와 위치는 리스폰과 함께 초기화되는 것이 자연스럽고, 플레이어 이름·팀·점수는 PlayerState에 남아 있을 수 있다.

## 규칙과 상태의 분리

```text
GameMode
  → 플레이어가 죽으면 리스폰할지, 게임 오버할지 결정

GameState
  → 현재 라운드 시간, 진행 여부, 팀 점수 같은 결정 결과를 보관·공유
```

GameMode는 월드 전체 규칙의 도메인/비즈니스 로직 결정권자에 가깝다. 다만 Character와 Component의 세부 행동까지 모두 GameMode에 몰아넣지는 않는다.

## Component와 lifetime

```text
Character
  ├─ CharacterMovementComponent
  ├─ HealthComponent
  ├─ InventoryComponent
  └─ InteractionComponent
```

Component는 Actor/Character가 소유하는 기능 조각으로 생각할 수 있다. 일반 C++의 구성(composition)과 RAII 소유 관계 감각은 도움이 되지만, Unreal에서는 UObject/Actor/Component lifecycle과 reflection 규칙이 실제 정리를 담당한다.

Unity의 `MonoBehaviour`와 비슷하게 GameObject에 붙는 기능 단위라는 감각은 유효하다. 다만 Unreal은 생성·등록·파괴와 reflection 규칙이 C++ 코드에 더 직접 드러난다.
