import os, sys, subprocess

TEST_SETTINGS = {
	30: 25,
	40: 25,
	50: 25,
	60: 25,
	70: 25,
	80: 25,
	90: 25,
	100: 25,
}
def currentDirectory() -> str:
	return os.path.dirname(os.path.abspath(__file__))
os.chdir(currentDirectory())

def makeTest(ctrl: int) -> str:
	process = subprocess.run(["../build/DataCreation", "--n", "4", "--ctrl", str(ctrl)], capture_output=True)
	return process.stderr.decode().split()[1]

sys.stdout = open("statistics.csv", "+a")
columns = ["n", "ctrl", "filename", "algo_name", "expanded_nodes", "time", "count_steps", "steps"]
print(*columns, sep="\t")
for ctrl in TEST_SETTINGS:
	COUNT = TEST_SETTINGS[ctrl]
	for i in range(COUNT):
		inputFile = makeTest(ctrl)
		fInput = open(inputFile, "r")
		try:
			process = subprocess.run(["../build/SearchingAlgorithms"], stdin=fInput, capture_output=True, timeout=180)
			output = process.stdout.decode().split(sep = '\n')
			for group in range(0, len(output), 4):
				if (group + 3 >= len(output)): break
				name = output[group][6:]
				expanded_nodes = output[group + 1].split()[-1]
				steps = output[group + 2].split()[-1]
				count_steps = len(steps)
				time = float(output[group + 3].split()[-1])
				data = [4, ctrl, inputFile, name, expanded_nodes, time, count_steps]
				print(*data, sep = '\t')
			print("ctrl = {} | done test {}".format(ctrl, i + 1), file=sys.stderr)
		except subprocess.TimeoutExpired:
			print("ctrl = {} | test {} is too hard ({})".format(ctrl, i + 1, inputFile), file=sys.stderr)
