#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**PLEASE READ!
 I have used numbers to represent different elements of the matrix:
 99 = Exit
 -4 = Impassable block
 66 = Robot
 0 = Free space
 
 
 Also, if there is any code that is commented out, I previously used it for testing purposes and have chose to leave it in for later reference.**/

int gen (){ //generates a random number from 0-7. this function is used in others to generate positions.
    int a = rand() % 8;
    return a;
}


int obst (int matrix[8][8], int a, int b){ //generates the position of the obstructions, using the gen function.
    int i = 0;
	
	for(i = 0; i < 10; i++){
        a = gen();
        b = gen();
        if(matrix[a][b] == -4 || matrix[a][b] == 99){
            i--;
            continue;
        }else{
            matrix[a][b] = -4;
        }
    }
    return 0;
    
}

int robotpos (int matrix[8][8], int *r1, int *r2){ //generates the position of the robot, using the gen function.
    do{
        *r1 = gen();
        *r2 = gen();
        
        matrix[*r1][*r2] = 66;
    } while(matrix[*r1][*r2] == -4 || matrix[*r1][*r2] == 99);
    
    return 0;
    
}

int mLeft(int matrix[8][8], int i, int j, int *n){ /**first is sure that j isn't 0, because that would be "out of bounds". looks at the position left of [i][j] 
and makes sure it is 0 or the current value of n + 1. finally, if this is true, then it makes the index down from [i][j] = to the value of n plus 1.**/
    int a = 0;
	
	if(j != 0){
		if((matrix[i][j-1] == 0)|| (matrix[i][j-1] == (*n) + 1)){
                	matrix[i][j-1] = (*n) + 1;
                	a = 1;
                	return a;
        }
    }else{
        a = 0;
        return a;
	}
    return 0;
}

int mRight(int matrix[8][8], int i, int j, int *n){ /**first is sure that j isn't 7, because that would be "out of bounds". looks at the position right of [i][j] 
and makes sure it is 0 or the current value of n + 1. finally, if this is true, then it makes the index down from [i][j] = to the value of n plus 1.**/
    int a = 0;
	
	if(j != 7){
		if((matrix[i][j+1] == 0) || (matrix[i][j+1] == (*n) + 1)){
                	matrix[i][j+1] = (*n) + 1;
                	a = 1;
                	return a;
    	}
    }else{
    	a = 0;
    	return a;
	}
    return 0;
}

int mUp(int matrix[8][8], int i, int j, int *n){ /**first is sure that i isn't 0, because that would be "out of bounds". looks at the position up from [i][j] 
and makes sure it is 0 or the current value of n + 1. finally, if this is true, then it makes the index down from [i][j] = to the value of n plus 1.**/
    int a = 0;
	
	if(i != 0){
		if((matrix[i-1][j] == 0)|| (matrix[i-1][j] == (*n) + 1)){
                	matrix[i-1][j] = (*n) + 1;
                	a = 1;
                	return a;
    	}
    }else{
    	a = 0;
    	return a;
	}
    return 0;
}

int mDown(int matrix[8][8], int i, int j, int *n){ /**first is sure that i isn't 7, because that would be "out of bounds". looks at the position down from [i][j] 
and makes sure it is 0 or the current value of n + 1. finally, if this is true, then it makes the index down from [i][j] = to the value of n plus 1.**/
   int a = 0;
   
    if(i != 7){
		if((matrix[i+1][j] == 0)|| (matrix[i+1][j] == (*n) + 1)){
                	matrix[i+1][j] = (*n) + 1;
                	a = 1;
                	return a;
    	}
    }else{
    	a = 0;
    	return a;
	}
    return 0;
}

//all of the mX functions return a value of either 1 or 0. these values are used in the loop that generates the steps away from the robot.

int pathfind (int matrix[8][8]){ //calculating the possible paths to the exit, using mUp, mDown, mLeft, and mRight.
    
    int i = 0;
    int j = 0;
    int y = 0;
    int x = 0;
    int changes = 0;
    int n = 1;
    int a = 0, b = 0, c = 0, d = 0;
    int z = 0; //this variable is going to be used to keep track if there was at least one occurance of a zero/a change in the matrix during that iteration
    
    
    for(i = 0; i < 8; i++){ //this loop finds the position of the robot on the matrix and then assigns its column value as y, and its row value as x.
        for(j = 0; j < 8; j++){
            if(matrix[i][j] == 66){
                y = i;
                x = j;
                
                break;
            }
        }
    }
    
    if(y < 8){
		if(matrix[y+1][x] != -4 && matrix[y+1][x] != 99){ //this, and the following if statements, look in four directions from the robot and make those indexes = 1
	        if(y < 7){
	            matrix[y+1][x] = 1;
	        }
	    }
}
    
    if(matrix[y-1][x] != -4 && matrix[y-1][x] != 99){
        if(y > 0){
            matrix[y-1][x] = 1;
        }
    }
    
    if(x < 8){
		if(matrix[y][x+1] != -4 && matrix[y][x+1] != 99){
	        if(x < 7){
	            matrix[y][x+1] = 1;
	        }
	    }
}
    
    if(matrix[y][x-1] != -4 && matrix[y][x-1] != 99){
        if(x > 0){
            matrix[y][x-1] = 1;
        }
    }
    
    //prmatrix(0, 0, matrix);
    
    do{
    //printf("Adding number %i ..\n", n+1);
        for (i = 0; i < 8; i++){
    		for(j = 0; j < 8; j++){
    			if(matrix[i][j] == n){
					changes = 0;
					a = mLeft(matrix, i, j, &n);
                	b = mRight(matrix, i, j, &n);
    				c = mUp(matrix, i, j, &n); 
                	d =  mDown(matrix, i, j, &n);
                	
                	changes = a + b + c + d + z;
                	if(changes > 0){
                		z++;
                	}
                    //printf("Added number %i around  [%i][%i]..   Values - Left %i, Right %i , Up %i , Down %i", n+1,i,j,a,b,c,d);
                    //prmatrix(0, 0, matrix);
    			}
    		}
    	}
    	n++;
    	z = 0;
        //printf("Completed loop %d ..   Values - a %d, b %d , c %d , d %d\n", n,a,b,c,d);
        //prmatrix(0, 0, matrix);
        
	}while(changes > 0);
    return 0;
}

int shortpath (int matrix[8][8], int *k, char direction[20]){ //this function looks at the spots next to [i][j]
    //it then looks around for a block with a value that is less than the value that the block has, and moves there
    int i = 0;
    int j = 7;
    int q = 0; //to run my lookx functions
    
	for(q = 0; q < 30; q++){ //i have chosen to use a for loop that iterates 30 times because the while loop busted the program!
    
        if(i > 0){
			i = lookup(matrix, &i, &j, k, direction); //this group of functions in this for loop looks in four directions for a new [i][j]
	 } 
        if(i < 7){
			i = lookdown(matrix, &i, &j, k, direction);
		}
		if(j > 0){
        	j = lookleft(matrix, &i, &j, k, direction);
     }
    	if(j < 7){
        	j = lookright(matrix, &i, &j, k, direction);
    	}
    }
    return 0;
}

int lookup (int matrix[8][8], int *i, int *j, int *k, char direction[20]){ /**this, and the following functions, look to see if a tile away from the current tile
is less than the current tile and is not -4. if that's true, a character representing that direction is put into the direction array, and a variable is
decremented, changing the actual position of [i][j]. if it does not meet the requirements of that if statement, it looks for 66, and does something similar.
if neither if statement is used, then a variable is returned.**/
	
	if(matrix[*i-1][*j] < matrix[*i][*j] && matrix[*i-1][*j] != -4){
		if(matrix[*i][*j] == 66){
			return *i;
		}else{
        direction[*k] = 'U';
        (*i)--;
        (*k)++;
        return *i;
    	}
    }
    else if(matrix[*i-1][*j] == -4){
    	return *i;
    }
    else if(matrix[*i-1][*j] == 66){
    	direction[*k] = 'U';
    	(*i)--;
    	(*k)++;
    	return *i;
	}else{
    return *i;
	}
	return *i;
}

int lookdown (int matrix[8][8], int *i, int *j, int *k, char direction[20]){
    if(matrix[*i+1][*j] < matrix[*i][*j] && matrix[*i+1][*j] != -4){
    	if(matrix[*i][*j] == 66){
			return *i;
		}else{
        	direction[*k] = 'D';
        	(*i)++;
        	(*k)++;
        	return *i;
    }
}
	else if(matrix[*i+1][*j] == -4){
		return *i;
	}
    else if(matrix[*i+1][*j] == 66){
    	direction[*k] = 'D';
    	(*i)--;
    	(*k)++;
    	return *i;
	}else{
    	return *i;
	}
	return *i;
}

int lookleft (int matrix[8][8], int *i, int *j, int *k, char direction[20]){
    if(matrix[*i][*j-1] < matrix[*i][*j] && matrix[*i][*j-1] != -4){
    	if(matrix[*i][*j] == 66){
			return *j;
		}else{
        	direction [*k] = 'L';
        	(*j)--;
        	(*k)++;
        	return *j;
    }
}
	else if(matrix[*i][*j-1] == -4){
		return *j;
	}
    else if(matrix[*i][*j-1] == 66){
    	direction[*k] = 'L';
    	(*j)--;
    	(*k)++;
    	return *j;
	}else{
    	return *j;
	}
	return *j;
}

int lookright (int matrix[8][8], int *i, int *j, int *k, char direction[20]){
    if(matrix[*i][*j+1] < matrix[*i][*j] && matrix[*i][*j+1] != -4){
    	if(matrix[*i][*j] == 66){
			return *i;
		}else{
        	direction[*k] = 'R';
        	(*j)++;
        	(*k)++;
        	return *j;
    }
}
	else if(matrix[*i][*j+1] == -4){
		return *j;
	}
    else if(matrix[*i][*j+1] == 66){
    	direction[*k] = 'R';
    	(*j)++;
    	(*k)++;
    	return *j;
	}else{
    return *j;
	}
	return *j;
}

int stepstaken (char direction[20], int *k, int matrix[8][8]){ /**this function first looks in the direction array and changes each value to its opposite. after that,
it prints out the directions that the robot went by printing the direction array, element by element.**/
    int i = 0;
    int j = 0;
    
    for(j = 0; j < *k; j++){ //this loop is changing each direction to its opposite counterpart
        if (direction[j] == 'U'){
            direction[j] = 'D';
        }
        else if (direction[j] == 'D'){
            direction[j] = 'U';
        }
        else if (direction[j] == 'L'){
            direction[j] = 'R';
        }
        else if (direction[j] == 'R'){
            direction[j] = 'L';
        }
    }
    
    int n;
    
    if(matrix[0][7] == 66){
    	printf("The robot did not have to go anywhere to reach the exit. It appeared on it.\n");
    }
    else if(matrix[0][6] == -4 && matrix [1][7] == -4 || matrix[0][7] == -4){
			printf("Sorry, the robot cannot make it to the exit, because the exit is blocked..\n");
		}  	
	else if(matrix[0][6] == 66){
		printf("The robot went R to get to the exit.\n");
	}
	else if(matrix[1][7] == 66){
		printf("The robot went U to get to the exit.\n");
	}else{
		if(matrix[0][6] == 0 && matrix[1][7] == 0){
			printf("Sorry, the robot cannot make it to the exit, because the exit is blocked..\n");
		}
		else if(matrix[0][6] != -4 || matrix [1][7] != -4){
			printf("\n\nThe robot went ");
		    if(matrix[0][6] >= matrix[1][7] && matrix[1][7] != -4){
		    	n = matrix[1][7];
		    	for(i = 0; n + 1 > i; n--){
		    		printf(" %c ", direction[n]);
		    	}
		    }
		    else if(matrix[0][6] >= matrix[1][7] && matrix[1][7] == -4){
		    	n = matrix[0][6];
		    	for(i = 0; n + 1 > i; n--){
		    		printf(" %c ", direction[n]);
		    	}
		    }
		    else if(matrix[0][6] <= matrix[1][7] && matrix[0][6] != -4){
		    	n = matrix[0][6];
		    	for(i = 0; n + 1 > i; n--){
		    	printf(" %c ", direction[n]);
		    	}
		    }
		    else if(matrix[0][6] <= matrix[1][7] && matrix[0][6] == -4){
		    	n = matrix[1][7];
		    	for(i = 0; n + 1 > i; n--){
		    	printf(" %c ", direction[n]);
		    	}
		    }
			printf(" to get to the exit.\n");
		    return 0;
		}
	}
    return 0;
}

void prmatrix (int matrix[8][8]){ //printing the graphical representation of the matrix
    int i = 0;
    int j = 0;
	
	for(i = 0; i < 8; i++){
        printf("\n|");
        for(j = 0; j < 8; j++){
            if(matrix[i][j] >= 10 || matrix[i][j] < 0){
                printf(" %i|", matrix[i][j]);
            }else{
                printf(" %i |", matrix[i][j]);
            }
        }
    }
    printf("\n\nKey:\nRobot: 66\nBlocks: -4\nExit: 99\nFree Spot: 0");
    printf("\n\n\n");
}


void initMatrix (int matrix[8][8]){ //making every value be equal to 0
    int i = 0;
    int j = 0;
	
	for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            matrix[i][j] = 0;
        }
    }
    
}

int main(){
    int matrix[8][8] = {0};
    char direction[20]; //to store the way that the robot gets to the exit
    
    int r1;
    int r2;
    int a;
    int b;
    int k = 0;
    
    srand((int)time(NULL));
    
    initMatrix(matrix); //making all values = 0.
    
    matrix[0][7] = 99; //setting the position of the exit. note that it is before the obstructions are generated, so it may be overwritten.
    
    prmatrix(matrix); //print to see empty matrix.
    
    obst(matrix, a, b); //generates the position of the obstructions, using the gen function.
    
    robotpos(matrix, &r1, &r2); //generates the position of the robot, using the gen function.
    
    prmatrix(matrix); //printing the graphical representation of the matrix.
    
    pathfind(matrix); //generating the possible paths for the robot to take.
    
    prmatrix(matrix);
    
    shortpath(matrix, &k, direction); //finding the shortest path of all generated paths made by pathfind() by looking in four directions.
    
    //prmatrix(matrix);
    
    stepstaken(direction, &k, matrix); //printing out the steps taken by the robot to get to the exit.
    
    system("PAUSE");
    return 0;
}
