import random

# Difficulty = height x width mines

# Custom
# Uncovered - .
# Marked mines - !
# Questionable mines - ?
# Numbers - #
# Blank tiles - 


# How should the text files be formatted?
# What are the default sizes for each world (nxm)?
	# Beginner = 9x9 10 mines
	# Intermediate = 16x16 40 mines
	# Expert = 16x30 99 mines
# Modes: debug, myAI(), rmanualAI()


class World():

	# Tiles
	class __Tile():
		mine = False
		number = 0


	def __init__(self, filename=None):
		self.__numMines = 0

		# If file is provided
		if filename != None:
			with open(filename, 'r') as file:
				self.__colDimension, self.__rowDimension = [int(x) for x in file.readline().split()]
				self.__board = [[self.__Tile() for i in range(self.__rowDimension)] for j in range(self.__colDimension)]
				self.__addFeatures(file)

		# If file not provided (default)
		else:
			self.__colDimension = 9		# Default sizes               What is the ratio from dimensions to mines?
			self.__rowDimension = 9		# Default size
			self.__totalMines = 10		# Default number of mines

			self.__board = [[self.__Tile() for i in range(self.__rowDimension)] for j in range(self.__colDimension)]
			self.__addFeatures()
		self.printBoard()


	def __addFeatures(self, open_file=None):
		""" Add mines and numbers to tiles """

		# If no file is provided (default)
		if open_file == None:
			currentMines = 0
			while currentMines < 10:
				r = self.__randomInt(9)
				c = self.__randomInt(9)
				if not self.__board[c][r].mine:
					self.__addMine(c, r)
					currentMines += 1

		# If file is provided
		else:
			for r, line in zip(range(self.__rowDimension - 1, -1, -1), open_file.readlines()):
				for c, tile in zip(range(0, self.__colDimension - 1, 1), line.split()):
					if tile == "1":
						self.__addMine(c, r)
				

	def __addMine(self, c, r):
		""" Add mine to tile located at c, r """

		# Set attributes
		self.__board[c][r].mine = True
		self.__numMines += 1		

		# Increment number values according to mines
		self.__addHintNumber(c, r+1)
		self.__addHintNumber(c, r-1)
		self.__addHintNumber(c+1, r)
		self.__addHintNumber(c-1, r)
		self.__addHintNumber(c-1, r+1)
		self.__addHintNumber(c+1, r+1)
		self.__addHintNumber(c-1, r-1)
		self.__addHintNumber(c+1, r-1)
		"""
		self.__board[c][r+1].number += 1		# Above
		self.__board[c][r-1].number += 1		# Below
		self.__board[c+1][r].number += 1		# Right
		self.__board[c-1][r].number += 1		# Left
		self.__board[c-1][r+1].number += 1		# Upper left
		self.__board[c+1][r+1].number += 1		# Upper right
		self.__board[c-1][r-1].number += 1 		# Lower left
		self.__board[c+1][r-1].number += 1		# Lower right
		"""

		# For every tile where number = 0 AND mine = false, it is considered blank


	def __addHintNumber(self, c, r):
		""" Makes sure tile is in bounds before updating the number value
			Avoids out of bounds IndexError
		"""

		if c < self.__colDimension and c >= 0 and r < self.__rowDimension and r >= 0:
			self.__board[c][r].number += 1


	def __printBoard(self):
		""" Print board for debugging """

		board_as_string = ""
		for r in range(self.__rowDimension - 1, -1, -1):
			for c in range(self.__colDimension):
				if self.__board[c][r].mine:
					board_as_string += " B "
				elif self.__board[c][r].number != 0:
					board_as_string += " " + str(self.__board[c][r].number) + " "
				else:
					board_as_string += " . "
			board_as_string += "\n"
		print(board_as_string)

	
	#####################################################
	#		         HELPER FUNCTIONS					#
	#####################################################
	def __randomInt(self, limit):
		""" Return a random int within the range from 0 to limit """

		return random.randrange(limit)

if __name__ == "__main__":
	world1 = World(filename="test_world.txt")
	world2 = World()
