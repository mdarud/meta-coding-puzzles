# Meta Coding Puzzles Solutions

This repository contains solutions to Meta's coding puzzles in both Python and C++. The puzzles are organized by difficulty level: Warmup, Level 1, and Level 2.

## Repository Structure

```
.
├── Warmup/           # Warmup problems (easiest)
│   ├── cpp/          # C++ solutions
│   └── py/           # Python solutions
├── Level 1/          # Level 1 problems (intermediate)
│   ├── cpp/          # C++ solutions
│   └── py/           # Python solutions
└── Level 2/          # Level 2 problems (advanced)
    ├── cpp/          # C++ solutions
    └── py/           # Python solutions
```

## Problems

### Warmup
- **ABCs**: Calculate the sum of three integers.
- **AllWrong**: Generate a string where each character is different from a given string.
- **Battleship**: Calculate the probability of hitting a battleship on a grid.

### Level 1
- **Cafeteria**: Maximize the number of students that can be seated in a cafeteria.
- **DirectorOfPhotography**: Count artistic photographs based on specific criteria.
- **Kaitenzushi**: Maximize the number of dishes a customer can eat.
- **RotatoryLock**: Find the minimum number of rotations to unlock a lock.
- **ScoreboardInference**: Infer possible scores from partial information.
- **StackStabilization**: Find the minimum cost to stabilize a stack.
- **UniformIntegers**: Count integers with all digits the same.

### Level 2
- **DirectorOfPhotography2**: An extension of the Level 1 problem with additional constraints.
- **Hops**: Find the minimum time for frogs to reach the shore.
- **MissingMail**: Optimize delivery schedules with missing packages.
- **Portals**: Find the shortest path through a grid with portals.
- **RabbitHole**: Navigate through a complex graph structure.
- **RotatoryLock2**: An extension of the Level 1 problem with multiple dials.
- **ScoreboardInference2**: An extension of the Level 1 problem with more complex inference.
- **TunnelTime**: Find the optimal path through tunnels with time constraints.

## How to Run

### Python Solutions
```bash
python <file_path>
```

Example:
```bash
python Warmup/py/ABCs.py
```

### C++ Solutions
```bash
g++ -std=c++14 <file_path> -o solution
./solution
```

Example:
```bash
g++ -std=c++14 Warmup/cpp/ABCs.cpp -o solution
./solution
```

## Solution Format

Each solution file includes:
1. Problem description
2. Constraints
3. Solution approach with time and space complexity analysis
4. Implementation
5. Test cases

## Contributing

Feel free to add more efficient solutions or additional test cases. When contributing:
1. Follow the existing file structure and naming conventions
2. Include comprehensive comments explaining your approach
3. Add test cases to validate your solution
4. Ensure your solution passes all test cases
