# ForFun Graph Library

## Test graphs

### Graph 1

Six-node tree.

```mermaid
flowchart TB
    id1((1)) --- id2((2))
    id1      --- id3((3))
    id1      --- id4((4))

    id4      --- id5((5))

    id5      --- id6((6))
```

### Graph 2

Eight-node graph with a cycle.

```mermaid
flowchart TB
    id1((a)) --- id2((b))
    id1      --- id3((c))
    id1      --- id4((d))

    id4      --- id5((e))

    id5      --- id6((f))
    id5      --- id7((g))

    id6      --- id8((h))

    id7      --- id8
```

### Graph 3

Balanced twelve-node binary tree.

```mermaid
flowchart TB
    id1((a)) --- id2((b))
    id1      --- id3((c))

    id2      --- id4((d))
    id2      --- id5((e))

    id3      --- id6((f))
    id3      --- id7((g))

    id6      --- id8((h))
    id6      --- id9((i))

    id7      --- id10((j))
    id7      --- id11((k))
```

### Graph 4

Unbalanced twelve-node binary tree.

```mermaid
flowchart TB
    id1((a)) --- id2((b))
    id1      --- id3((c))

    id2      --- id4((d))
    id2      --- id5((e))

    id3      --- id6((f))
    id3      --- id7((g))

    id6      --- id8((h))
    id6      --- id9((i))

    id7      --- id10((j))
    id7      --- id11((k))
    id10     --- id12((l))
```
