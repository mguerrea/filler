#!/usr/bin/python
import sys
import time
import subprocess

rest = ""

p1 = ""
p2 = ""

p1Replacement = "\033[32m" + u"\u2588" + "\033[0m"
p2Replacement = "\033[34m" + u"\u2588" + "\033[0m"

sleepDelay = 0.05

def getPlayers():
	global p1
	global p2

	while True:
		line = sys.stdin.readline()
		if line.startswith("$"):
			try:
				p1 = line.split("/")[-1].split(".")[-2]
		 	except:
				return False

			sys.stdin.readline()
			line = sys.stdin.readline()

			try:
				p2 = line.split("/")[-1].split(".")[-2]
			except:
				return False
			return True

def getNextMap():
	global rest

	result = ""
	showHasStarted = False

	rest = ""
	while True:
		line = sys.stdin.readline()
		rest += line
		try:
			if line[0].isdigit():
				showHasStarted = True
				result += ''.join([i for i in line if not i == ' ' and not i.isdigit()])
			elif showHasStarted:
				break
		except:
			return ""

	return result

def displayScore():
	global rest

	p1Score = 0
	p2Score = 0
	lines = rest.split("\n")

	for line in lines:
		if line.count("==") == 1 and line.count(":") == 1:
			if line.count("O") == 1:
				p1Score = int(line.split(":")[1])
			if line.count("X") == 1:
				p2Score = int(line.split(":")[1])
	print(p1 + ": " + str(p1Score) + " / " + p2 + ": " + str(p2Score))
	if p1Score > p2Score:
		print(p1 + " is the winner!")
	elif p2Score > p1Score:
		print(p2 + " is the winner!")
	else:
		print("It's a draw")

def prettyPrintGame():
	global sleepDelay
	global p1Replacement
	global p2Replacement

	while True:
		line = getNextMap()
		if line == "":
			break
		else:
			sys.stderr.write("\x1b[2J\x1b[H")
			# subprocess.call(["clear"])

		line = line.replace(".", " ")
		line = line.replace("o", p1Replacement).replace("O", p1Replacement)
		line = line.replace("x", p2Replacement).replace("X", p2Replacement)

		print (line)
		time.sleep(sleepDelay)
	displayScore()

def main():
	if getPlayers() == True:
		prettyPrintGame()
	else:
		print("BAD INPUT")

if __name__ == "__main__":
	main()