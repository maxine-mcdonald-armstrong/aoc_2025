import re
from ortools.linear_solver import pywraplp
# why come up with a smart algorithm when you can just use ILP :)

def parse_line(line):
    target_match = re.search(r'\[([.#]+)\]', line)
    target = target_match.group(1) if target_match else ""

    buttons = []
    for match in re.findall(r'\((.*?)\)', line):
        if match.strip() == "":
            buttons.append([])
        else:
            buttons.append([int(x) for x in match.split(',')])

    values_match = re.search(r'\{(.*?)\}', line)
    values = [int(x) for x in values_match.group(1).split(',')] if values_match else []

    return target, buttons, values


sol = 0
# with open("template.txt", "r") as f:
with open("in.txt", "r") as f:
    lines = f.readlines()
    for line in lines:
        target, buttons, values = parse_line(line)
        solver = pywraplp.Solver.CreateSolver("SCIP")
        vars = []
        for i, button in enumerate(buttons):
            v = solver.IntVar(0, max(values), f"v{i}")
            vars.append(v)
        for i, t in enumerate(values):
            to_constrain = []
            for j, button in enumerate(buttons):
                if i in button:
                    to_constrain.append(j)
            solver.Add(sum(vars[j] for j in to_constrain) == t)
        solver.Minimize(sum(vars))
        status = solver.Solve()
        sol += sum([v.solution_value() for v in vars])
        print(sol)
print(sol)

