package src;

import java.util.*;
import java.io.*;

public class WorldGenerator {

	public static void main(String[] args) throws Exception {
		Scanner input = new Scanner(System.in);
		System.out.println("Number of Worlds: ");
		int nWorlds = input.nextInt();
		
		System.out.println("# Rows: ");
		int row = input.nextInt();
		
		System.out.println("# Cols: ");
		int col = input.nextInt();
		
		System.out.println("# Bombs: ");
		int nBombs = input.nextInt();
		
		input.close();
		
		System.out.println("Creating " + nWorlds
				+ " worlds of size " 
				+ row + "x" 
				+ col + " with " 
				+ nBombs + " each...");
		
		// Create a new directory of worlds. If directory already exists, delete it
		File worldDir = new File("generated_worlds");
		if (worldDir.exists()) {
			System.out.println("Deleting worlds Directory...");
			worldDir.delete();
		}
		
		System.out.println("Creating new Worlds Directory...");
		worldDir.mkdir();
		
		String worldDirPath = worldDir.getPath();
		
//		int nWorlds = 100;
//		int nBombs = 10;
//		int row = 6;
//		int col = 6;
		for (int i = 0; i < nWorlds; i++) {
			String newFilePath = worldDirPath + "/" + i + ".txt";
			File newWorld = new File(newFilePath);
			newWorld.createNewFile();
			
			// Print row col
			PrintWriter output = new PrintWriter(newWorld);
			output.println(row + " " + col);
			
			// Print starting coords
			int stX = (int) (Math.random() * col) + 1;
			int stY = (int) (Math.random() * row) + 1;
			output.println(stX + " " + stY);
			
			// Print bomb grid
			int[][] bombs = new int[row][col];
			init(bombs);
			int j = nBombs;
			while (j > 0) {
				int y = (int) (Math.random() * row) + 1;
				int x = (int) (Math.random() * col) + 1;
				// Do not place mine adjacent to starting tile
				if ((Math.abs(x-stX) > 1) && (Math.abs(y-stY) > 1)
					&& (Math.sqrt(Math.pow((y-stY),2) + Math.pow((x-stX),2))) > Math.sqrt(2)) {
					// place only if there isn't already a mine
					if (bombs[y-1][x-1] == 0) {
						bombs[y-1][x-1] = 1;
						j--;
					}
				}		
			}
			
			// Write bombs
			for (j = 0; j < row; j++) {
				for (int k = 0; k < col; k++) {
					output.print(bombs[j][k]);
					if (k != col-1) {
						output.print(" ");
					}
				}
				output.println();
			}
			output.close();
		}
		
		// Generate worlds and save them to directory
	}
	
	private static void init(int[][] bombs) {
		for (int i = 0; i < bombs.length; i++) {
			for (int j = 0; j < bombs[0].length; j++) {
				bombs[i][j] = 0;
			}
		}
	}
	
//	private void createRandomBoard(int stX, int stY) {
//		/*	Inputs:
//		 * 		stX - the starting x coordinate for this world. 
//		 * 		stY - the starting y coordinate for this world
//		 * 
//		 * 	Description:
//		 * 	Creates a default board with the given input coordinates
//		 * 	as the starting tile. Tiles that border the starting tile
//		 * 	are guaranteed to not be mines.
//		 *  
//		 *  Notes: 
//		 *  x,y coordinates are 1-indexed. That is,
//		 *  	1 <= x <= colDimension & 1 <= y <= rowDimension
//		 */
//		this.board = new Tile[DEFAULT_ROWS][DEFAULT_COLS];
//		TwoTuple rowCol = this.translateCoordinate(stX, stY);
//		int stRow = rowCol.x;
//		int stCol = rowCol.y;
//		this.initEmptyBoard();
//		
//		// Add Mines
//		int i = DEFAULT_MINES;
//		while (i > 0) {
//			int r = (int) (Math.random() * this.rowDimension);
//			int c = (int) (Math.random() * this.colDimension);
//			// Do not place mine adjacent to starting tile
//			if (Math.abs(r-stRow) > 1 || Math.abs(c-stCol) > 1) {
//				// place only if there isn't already a mine
//				if (!this.board[r][c].mine) {
//					this.addMine(r, c);
//					i--;
//				}
//			}	
//		}
//	}
//	

}
