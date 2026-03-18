# Argument Parser Design

We want to represent the argument parser as a state machine.
However, the naive approach leads to a extremely huge state machine with lots of redundant states.
For example, if we have a program with 3 mandatory cli arguments, then we have $3! = 6$ possible paths leading to an accepting state. In total we would have $n \cdot (\Sigma_{i=2}^{n} i) = 3 \cdot (3 + 2) = 15$ states.
This is leadst to a combinatorial explosion and I am too lazy to deal with this.

```mermaid
---
title: Naive State Machine for 3 Arguments
---
stateDiagram-v2
    [*] --> 1_Arg1
    1_Arg1 --> 1_Arg2
    1_Arg2 --> 1_Arg3
    1_Arg3 --> [*]

    1_Arg1 --> 2_Arg3
    2_Arg3 --> 2_Arg2
    2_Arg2 --> [*]

    [*] --> 3_Arg2
    3_Arg2 --> 3_Arg1
    3_Arg1 --> 3_Arg3
    3_Arg3 --> [*]

    3_Arg2 --> 4_Arg2
    4_Arg2 --> 4_Arg1
    4_Arg1 --> [*]

    [*] --> 5_Arg3
    5_Arg3 --> 5_Arg1
    5_Arg1 --> 5_Arg2
    5_Arg2 --> [*]

    5_Arg3 --> 6_Arg2
    6_Arg2 --> 6_Arg1
    6_Arg1 --> [*]
```

Therefore, I propose a simpler idea.
Instead of one large state machinem we use a sequence of small state machines.
Basically, we always use the same state machine, but remove paths which were already used.


```mermaid
---
title: State Machine Sequence 1
---
stateDiagram-v2
    [*] --> Arg1
    [*] --> Arg2
    [*] --> Arg3
    Arg1 --> [*]
    Arg2 --> [*]
    Arg3 --> [*]
```

Lets say we picked Arg1 first. Then the next state machine would be:

```mermaid
---
title: State Machine Sequence 2
---
stateDiagram-v2
    [*] --> Arg2
    [*] --> Arg3
    Arg2 --> [*]
    Arg3 --> [*]
```

Finally, the last state machine would be: 
```mermaid
---
title: State Machine Sequence 3
---
stateDiagram-v2
    [*] --> Arg3
    Arg3 --> [*]
```

This makes parsing very simple and short.