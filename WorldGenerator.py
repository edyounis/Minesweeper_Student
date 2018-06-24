# ==============================CS-199==================================
# FILE:			WorldGenerator.py
#
# AUTHOR: 		Justin Chung
#
# DESCRIPTION:	This file generates Worlds. The generator can be used to
#				create any number of worlds.
#
# NOTES: 		- Make sure to specify a number for difficulty:
#					1 --> Beginner
#					2 --> Intermediate
#					3 --> Expert
#				
#				- DO NOT MAKE CHANGES TO THIS FILE.
# ==============================CS-199==================================

import random
import os
import argparse


def generateWorlds(numWorlds: int, difficulty: int, baseFileName: "string") -> None:
	""" Generates N random worlds of a specified difficulty """
	""" Each generated world will be a text file with baseFileName followed by a number """
	for i in range(1, numWorlds+1):
		createWorldFile(difficulty, baseFileName+str(i))


def createWorldFile(difficulty: int, filename: "string") -> None:
	""" Create a single Minesweeper world file """
	print("Creating world " + filename + "...")
	
	directory_name = os.path.abspath("Worlds")
	file_path = os.path.join(directory_name, filename+".txt")

	# Set difficulty
	if difficulty == 1:
		nRows, nCols = 8, 8
		nMines = 10
	elif difficulty == 2:
		nRows, nCols = 16, 16
		nMines = 40
	elif difficulty == 3:
		nRows, nCols = 16, 30
		nMines = 99

	# Randomly set the starting tile
	startX = __randomInt(nCols+1)
	startY = __randomInt(nRows+1)
	startingPatch = [(startX, startY)]

	# Surrounding tiles can't have a mine
	for coord in [(-1, 1), (0, 1), (1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0)]:
		if __isInBounds(startX+coord[0], startY+coord[1], nRows, nCols):
			startingPatch.append((startX+coord[0], startY+coord[1]))
	
	# Randomly place mines that aren't in startingPatch
	mineCoords = []
	currentMines = 0
	while currentMines < nMines:
		x = __randomInt(nCols)
		y = __randomInt(nRows)
		if (x, y) not in startingPatch and (x, y) not in mineCoords:
			mineCoords.append((x, y))
			currentMines += 1

	# Open file for writing
	try:
		with open(file_path, 'w') as file:
			# Write dimensions
			file.write(str(nRows) + " " + str(nCols) + "\n")
			# Write starting square
			file.write(str(startX) + " " + str(startY) + "\n")
			# Write 2D grid
			for y in range(nRows, 0, -1):
				for x in range(1, nCols+1):
					if (x, y) in mineCoords:
						file.write("1 ")
					elif (x, y) in startingPatch:
						file.write("x ")
					else:
						file.write("0 ")
				file.write("\n")
	except:
		print("ERROR: Failed to open file")


def __randomInt(limit: int) -> int:
	""" Return a random between 1 and limit """
	return random.randrange(1, limit)


def __isInBounds(x: int, y: int, nRows: int, nCols: int) -> bool:
	""" Check if x and y is within bounds """
	return (x >= 1 and x <= nCols and y >= 1 and y <= nRows)


def main():
	# Create parser
	parser = argparse.ArgumentParser(description="Process command line arugments for world generation")

	# Parse options																													# Help is default
	parser.add_argument("numFiles", help="Number of world files to create", action="store", type=int)								# Number of files
	parser.add_argument("difficulty", help="Beginner=1, Intermediate=2, Expert=3", action="store", type=int, choices=[1, 2, 3])		# Difficulty
	parser.add_argument("filename", help="Base filename", action="store")															# Base filename

	args = parser.parse_args()

	numFiles = args.numFiles
	difficulty = args.difficulty
	filename = args.filename
	
	generateWorlds(numFiles, difficulty, filename)


if __name__ == "__main__":
	main()
	