# Inductive graph

함수형 언어에서 그래프의 표현은 상당히 까다로운 주제다.

어떤 그래프 $G$는 $(V, E)$로 나타낼 수 있다. $V$는 정점 집합, $E: V \rightarrow V$ 의 매핑(간선 집합). 이 때 그래프 알고리즘은 보통 이 $G$에 덧붙여 방문한 노드 목록 혹은 사용한 간선 목록등의 정보를 추가로 관리해야하는데 이게 함수형 언어에서 짤 때 굉장히 고통스러워진다. 기존 자료구조에 이런 marking을 하는 것은 "stateful"한 동작이고 이게 상태가 없는 구조를 지향하는 함수형 언어에 별로 적합하지 않기 때문.

list나 tree의 경우 각 노드에 도착하는 방법 자체가 유일하기 때문에 이런 추가적인 정보의 관리가 필요 없다(애초에 재귀적으로 정의되는 구조기 때문).

그래서 list나 tree처럼 그래프를 inductive한 형태로 표현해보자 하는 발상이 inductive graph. 개념적으로 그래프를 두 종류의 생성자를 이용해 표현할 수 있다.

## 생성자

inductive graph는 그래프를 "빈 그래프" 혹은 "새로운 노드 v 및 기존 그래프 g로부터 v에 들어오는 / 나가는 엣지 집합으로 확장된 그래프" 두 종류로 생각한다.

```haskell
type Node = Int
type Adj b = [(b, Node)]
type Context a b = (Adj b, Node, a, Adj b)

data Graph a b = Empty | Context a b & Graph a b
```

실제로 위와 같은 방식으로 정의할 순 없지만 개념적으로 이렇게 생각할 수 있다. 마치 리스트처럼, 그래프를 빈 그래프(`Empty`) , 혹은 기존 그래프(`Graph a b`) 에 새로운 노드 및 엣지 집합(`Context a b`) 이 추가된 형태(`Context a b & Graph a b`) 로 생각할 수 있는 것이다.

예를 들어 위 정의를 이용해 그래프를 이런 방식으로 생성할 수 있다.

```haskell
g :: Graph Char String
g = ([("left", 2), ("up", 3), 1, 'a', [("right", 2)]) &
    ([], 2, 'b', [("down", 3)]) &
    ([], 3, 'c', []) & Empty
```





## 참고 자료

- [﻿Inductive Graphs and Functional Graph Algorithms (Martin erwig)](https://web.engr.oregonstate.edu/~erwig/papers/InductiveGraphs_JFP01.pdf)
- [Functional Programming With Graphs﻿](https://futtetennismo.me/posts/algorithms-and-data-structures/2017-12-08-functional-graphs.html)



