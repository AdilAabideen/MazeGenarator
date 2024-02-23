#!/bin/bash


# remove read permissions from this file to perfrom Bad permissions test
chmod -r data/bad_perms.csv

gcc Maze.c -o Maze

echo -e "~~ Argument Tests ~~"

# This test tests if no arguments have been passed to the program, No file passed
echo -n "Testing no arguments - "
./Maze > tmp
if grep -q "Usage: Maze <filename>" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if 2 argumnets have been given to the Program 
echo -n "Testing 2 argumnets - "
./Maze x x > tmp
if grep -q "Usage: Maze <filename>" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\n~~ File Handling~~"


# This test if the file loaded is not correct name or doesnt exist ( fake.csv doesnt exist )
echo -n "Testing Bad Filename - "
./Maze fake.csv > tmp
if grep -q "Error: Bad filename" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the data has missing fields, No S ( Start Point ) - bad_data_missing_s has no start point
echo -n "Testing Bad data ( missing start point ) - "
./Maze data/bad_data_missing_s.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the data has missing fields, No E ( End Point ) - bad_data_missing_e has no end point
echo -n "Testing Bad data ( missing End point ) - "
./Maze data/bad_data_missing_e.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the file has bad permissions, using bad_perms.csv
echo -n "Testing bad permissions - "
./Maze data/bad_perms.csv > tmp
if grep -q "Error: Bad filename" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This test tess if the data has irregular widths, if each row is not the same length using bad_data_irregular_width
echo -n "Testing Bad Data ( Irregular width ) - "
./Maze data/bad_data_irregular_width.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This test tess if the data has irregular height, if each collumn is not the same length using bad_data_irregular_height
echo -n "Testing Bad Data ( Irregular width ) - "
./Maze data/bad_data_irregular_height.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This test if the data in the file has a Width of greater than 100 -- File width is 119
echo -n "Testing bad Data ( Max Width ) - "
./Maze data/bad_data_max_width.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This test if the data in the file has a Width of less than 5 -- File width is 4
echo -n "Testing bad Data ( Min Width ) - "
./Maze data/bad_data_min_width.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This test tests if the file has a height over 100 - File height is 102 
echo -n "Testing bad data ( max Height ) - "
./Maze data/bad_data_max_height > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This test tests if the file has a height of less than 5 - File height is 3 
echo -n "Testing bad data ( Min Height ) - "
./Maze data/bad_data_min_height > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then 
    echo "PASS"
else
    echo "FAIL"
fi


# This test if there are any other characters in the file other than # S E, The file to be tested has many other characters
echo -n "Testing bad data ( Incorrect Characters ) - "
./Maze data/bad_data_incorrect_characters.csv > tmp
if grep -q "Error: CSV file does not have the expected format" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the file loads succesfully using original.csv
echo -n "Testing file loads Succesfully - "
./Maze data/original.csv > tmp
if grep -q "File data/original.csv successfully loaded" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\n~~ Bad user inputs ~~"


# This tests if the user inputs anything other than W A S D M, Nothing is inputted ""
echo -n "Testing bad menu input ( nothing ) - "
echo "" | ./Maze data/orignal.csv > tmp
if grep -q "Error : Invalid Movement character" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# This tests if the user inputs anything other than W A S D M, j is inputed
echo -n "Testing bad menu input ( wrong ) - "
echo "j" | ./Maze data/orignal.csv > tmp
if grep -q "Error : Invalid Movement character" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\n~~ Successful User Inputs ~~"


# This tests the forward Movement W key press by if it is clicked then the user will reach the end point and be treated with a success message
echo -n "Testing W ( forward Movement ) - "
echo "W" | ./Maze data/forward_movement.csv > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests the right Movement D key press by if it is clicked then the user will reach the end point and be treated with a success message
echo -n "Testing D ( Right Movement ) - "
echo "D" | ./Maze data/right_movement.csv > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests the downwards Movement S key press by if it is clicked then the user will reach the end point and be treated with a success message
echo -n "Testing S ( Downward Movement ) - "
echo "S" | ./Maze data/down_movement.csv > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests the left Movement A key press by if it is clicked then the user will reach the end point and be treated with a success message
echo -n "Testing A ( Left Movement ) - "
echo "A" | ./Maze data/left_movement.csv > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the User moves into the Walls amrked as # - A special file has been created with the Wall to the direct right so the D inputed will hit the Wall
echo -n "Testing Movement into Walls - "
echo "D" | ./Maze data/wall_movement.csv > tmp
if grep -q "Alert Cannot Move into the Walls marked as (#)" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the User moves into the edges beyond the Maze - A special file has been created with the start on the right edge so the D inputted will move it beyond
echo -n "Testing Movement beyond Edges - "
echo "D" | ./Maze data/edge_movement.csv > tmp
if grep -q "Alert Cannot Move beyond the maze" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# This tests if the Map is shown, by searching for a Message of map being shown when M has been entered 
echo -n "Testing Viewing of Image of Map - "
echo "M" | ./Maze data/original.csv > tmp
if grep -q "Successfully Shown Image of Map" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\n~~ Succesful Run~~"

# Testing if there is a succesful run in a 5x5 maze, with a .in input file we search for a Success message
echo -n "Testing Full run ( 5 x 5 ) - "
./Maze data/original.csv < inputs/success_5x5.in > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# Testing if there is a succesful run in a 10x6 maze, with a .in input file we search for a Success message
echo -n "Testing Full run ( 10 x 6 ) - "
./Maze data/original10x6.csv < inputs/success_10x6.in > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# Testing if there is a succesful run in a 15x8 maze, with a .in input file we search for a Success message ( Uses all Movement Key presses )
echo -n "Testing Full run ( 15 x 8 ) - "
./Maze data/original15x8.csv < inputs/success_15x8.in > tmp
if grep -q "Success - You have reached the Exit point" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# adding read perms back on to bad_perms.csv
chmod +r data/bad_perms.csv
# Tidy up and removing the tmp file
rm -f tmp