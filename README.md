# EASEA Evolutionary Algorithm Framework

## Overview

This repository contains implementations of various evolutionary algorithms using the EASEA (EAsy Specification of Evolutionary Algorithms) framework. EASEA provides a high-level language for defining genetic algorithms and genetic programming solutions.

## Files Description

### Scripts

- `compile.sh` - Compilation script for genetic programming implementations
- `compile2.sh` - Alternative compilation script with different parameters

### Evolutionary Algorithm Implementations

- `findfunc.ez` - Genetic programming implementation for finding a function matching Newton's law of gravity
- `regression.ez` - Standard genetic programming for polynomial regression (finding x³-3x²+x)
- `regressionInitial.ez` - Initial version of the regression implementation with fewer generations
- `gravitationuniv.ez` - Evolutionary algorithm for finding gravitational constants
- `sigdecomp.ez` - Signal decomposition into a sum of sine waves

## Usage

To compile and run a genetic programming implementation:

```bash
# Method 1
./compile.sh

# Method 2
easena -gp findfunc.ez
make
./findfunc --nbCPUThreads 10 --seed 2
make easeaclean
```

## Key Features

- **Genetic Programming** - Tree-based representation for evolving mathematical functions
- **Parameter Tuning** - Various configuration options for population size, mutation rates, etc.
- **Parallel Execution** - Support for multiple CPU threads
- **GPU Support** - Some implementations include options for CUDA-based execution

## Implementation Details

The implementations use various evolutionary techniques:
- Tournament selection
- Ramped half-and-half initialization
- Crossover and mutation operators
- Fitness evaluation based on squared error

Each .ez file contains sections for:
- User declarations (constants, data structures)
- User functions (data generation, utility functions)
- Life cycle hooks (before/after generation functions)
- Genome class definition
- Genetic operators (initialization, crossover, mutation)
- Evaluator functions
- Run parameters

## Example Problems

1. **Newton's Law of Gravity** (`findfunc.ez`) - Find the formula for gravitational force
2. **Polynomial Regression** (`regression.ez`) - Evolve a function to match x³-3x²+x
3. **Gravitational Constants** (`gravitationuniv.ez`) - Find Earth and Sun mass values
4. **Signal Decomposition** (`sigdecomp.ez`) - Decompose signals into constituent sine waves

## Requirements

- EASEA framework
- C++ compiler
- CUDA (optional, for GPU acceleration)
