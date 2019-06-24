from ortools.linear_solver import pywraplp
from ortools.sat.python import cp_model
from pathlib import Path

class RPQ():
    def __init__(self, r, p, q):
        self.R = r
        self.P = p
        self.Q = q



def MILP(jobs, instanceName):
    variablesMaxValue = 0
    for i in range(len(jobs)):
        variablesMaxValue += (jobs[i].R+jobs[i].P+jobs[i].Q)

    solver = pywraplp.Solver('simple_mip_program',
                             pywraplp.Solver.CBC_MIXED_INTEGER_PROGRAMMING)
    solver.StringParameters = "max_time_in_seconds:120.0" 

    #variables:
    alfasMatrix = {}
    for i in range(len(jobs)):
        for j in range(len(jobs)):
            alfasMatrix[i,j] = solver.IntVar(0,1,"alfa"+str(i)+"_"+str(j))
    starts = []
    for i in range(len(jobs)):
        starts.append(solver.IntVar(0, variablesMaxValue, "starts"+str(i)))
    cmax = solver.IntVar(0, variablesMaxValue, "cmax")

    #constrainsts:
    for i in range(len(jobs)):
        solver.Add(starts[i]>=jobs[i].R)
        solver.Add(cmax>=starts[i]+jobs[i].P+jobs[i].Q)

    for i in range(len(jobs)):
        for j in range(i+1, len(jobs)):
            solver.Add(starts[i] + jobs[i].P <= starts[j] + alfasMatrix[i,j] * variablesMaxValue)
            solver.Add(starts[j] + jobs[j].P <= starts[i] + alfasMatrix[j,i] * variablesMaxValue)
            solver.Add(alfasMatrix[i,j] + alfasMatrix[j,i] == 1)

    #solver
    solver.Minimize(cmax)
    status = solver.Solve()
    if(status is not pywraplp.Solver.OPTIMAL):
        print("Not optimal!")
    print(instanceName, "CMax:", solver.Objective().Value())
    pi = []
    for i in range (len(starts)):
        pi.append((i, starts[i].solution_value()))
    pi.sort(key=lambda x:x[1])
    print(pi)



def CP(jobs, instanceName):
    variablesMaxValue = 0
    for i in range(len(jobs)):
        variablesMaxValue += (jobs[i].R+jobs[i].P+jobs[i].Q)

    model = cp_model.CpModel()
    solver = cp_model.CpSolver()
    solver.StringParameters = "max_time_in_seconds:120.0" 

    cmax = model.NewIntVar(0, variablesMaxValue, "cmax")

    intervals = []
    job_vars = {}
    for i in range(len(jobs)):
        start_var = model.NewIntVar(0, variablesMaxValue, "start_"+str(i))
        end_var = model.NewIntVar(0, variablesMaxValue, "end_"+str(i))
        interval_var = model.NewIntervalVar(start_var, jobs[i].P,
                                            end_var, "interval_"+str(i))
        intervals.append(interval_var)
        job_vars[i] = ({'start': start_var, 'end': end_var})

    model.AddNoOverlap(intervals)

    for i in range(len(jobs)):
        model.Add(job_vars[i]['start'] >= jobs[i].Q)
        model.Add(job_vars[i]['end'] + jobs[i].Q <= cmax)

    #solver
    model.Minimize(cmax)
    status = solver.Solve(model)
    print(instanceName, "CMax:", solver.ObjectiveValue())
    starts = [(i, solver.Value(job_vars[i]['start'])) for i in range(len(jobs))]
    permutation = [i for i, _ in sorted(starts, key=lambda x: x[1])]
    print(permutation); 



def GetRPQsFromFile(pathToFile):
    fullTextFromFile = Path(pathToFile).read_text()
    words = fullTextFromFile.replace("\n"," ").split(" ")
    words_cleaned = list(filter(None, words))
    numbers = list(map(int, words_cleaned))

    numberOfJobs = numbers[0]
    numbers.pop(0)
    numbers.pop(0)

    jobs = []

    for i in range(numberOfJobs):
        jobs.append(RPQ(numbers[0], numbers[1], numbers[2]))
        numbers.pop(0)
        numbers.pop(0)
        numbers.pop(0)

    return  jobs

if __name__ == '__main__':
    file_paths = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"]

    for i in range(len(file_paths)):
        jobs = GetRPQsFromFile(file_paths[i])
        print("\n\nInstance name: ", file_paths[i])
        print("\nMilp: ")
        MILP(jobs, file_paths[i])
        print("\nCP: ")
        CP(jobs, file_paths[i])