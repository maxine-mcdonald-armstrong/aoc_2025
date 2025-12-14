import sys
from ortools.sat.python import cp_model

def get_hardcoded_shapes():
    shapes = [None for _ in range(6)]
    shapes[0] = frozenset([
        (0,0), (0,1), (0,2),
        (1,0), (1,1),
        (2,0)
    ])
    shapes[1] = frozenset([
        (0,0), (0,1),
        (1,0), (1,1), (1,2),
        (2,0), (2,2)
    ])
    shapes[2] = frozenset([
        (0,2),
        (1,1), (1,2),
        (2,0), (2,1)
    ])
    shapes[3] = frozenset([
        (0,0), (0,1), (0,2),
        (1,0),
        (2,0), (2,1), (2,2)
    ])
    shapes[4] = frozenset([
        (0,0), (0,2),
        (1,0), (1,1), (1,2),
        (2,0), (2,2)
    ])
    shapes[5] = frozenset([
        (0,2),
        (1,0), (1,1), (1,2),
        (2,0), (2,1), (2,2)
    ])
    return shapes

def parse_input(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    queries = []
    for line in lines:
        parts = line.split(':')
        dims = parts[0].strip()
        counts_str = parts[1].strip()
        width, height = map(int, dims.split('x'))
        counts = list(map(int, counts_str.split()))
        queries.append((width, height, counts))
    return queries

def normalize(coords):
    min_r = min(r for r, c in coords)
    min_c = min(c for r, c in coords)
    return frozenset((r - min_r, c - min_c) for r, c in coords)

def get_orientations(base_shape):
    variations = set()
    current = base_shape
    for _ in range(4):
        variations.add(normalize(current))
        # Flip
        flipped = frozenset((r, -c) for r, c in current)
        variations.add(normalize(flipped))
        # Rotate 90 degrees clockwise
        current = frozenset((c, -r) for r, c in current)
    return list(variations)

def solve_region(width, height, counts, all_shapes):
    model = cp_model.CpModel()
    candidates = []
    for s_idx, count in counts.items():
        shape_coords = all_shapes[s_idx]
        orientations = get_orientations(shape_coords)
        vars_for_this_shape = []
        for orient in orientations:
            shape_h = max(r for r, c in orient) + 1
            shape_w = max(c for r, c in orient) + 1
            for r in range(height - shape_h + 1):
                for c in range(width - shape_w + 1):
                    occupied_cells = []
                    for (sr, sc) in orient:
                        occupied_cells.append((r + sr, c + sc))
                    var = model.NewBoolVar(f'shape_{s_idx}_{r}_{c}')
                    candidates.append({
                        "var": var,
                        "cells": occupied_cells
                    })
                    vars_for_this_shape.append(var)
        if len(vars_for_this_shape) < count:
            return False
        model.Add(sum(vars_for_this_shape) == count)

    grid_coverage = {}
    for cand in candidates:
        for cell in cand["cells"]:
            if cell not in grid_coverage:
                grid_coverage[cell] = []
            grid_coverage[cell].append(cand["var"])
    for cell, vars_list in grid_coverage.items():
        model.Add(sum(vars_list) <= 1)

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    return status == cp_model.OPTIMAL or status == cp_model.FEASIBLE

shapes = get_hardcoded_shapes()
queries = parse_input("in.txt")
ans = 0
for i, (w, h, counts) in enumerate(queries):
    print(f"Region {i+1}: {w}x{h} ", end="", flush=True)
    total_area = w * h
    presents_area = 0
    for s_idx, count in counts.items():
        if s_idx in shapes:
            s_area = len(shapes[s_idx])
            presents_area += s_area * count
    if presents_area > total_area:
        print("0 (short-circuit)")
        continue
    if solve_region(w, h, counts, shapes):
        print("1")
        ans += 1
    else:
        print("0")
print(ans)

