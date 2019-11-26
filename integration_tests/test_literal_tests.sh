echo "-Test Symbolic Command Tests-"
echo

#test case 1
echo "test ../prototype" > commands.txt
truncate -s-1 commands.txt
echo "$ test ../prototype"
echo
../integration_test < commands.txt
echo

#test case 2
echo "test -f prototype" > commands.txt
truncate -s-1 commands.txt
echo "$ test -f prototype"
echo
../integration_test < commands.txt
echo

#test case 3
echo "test -d ../prototype" > commands.txt
truncate -s-1 commands.txt
echo "$ test -d ../prototype"
echo
../integration_test < commands.txt
echo

#test case 4
echo "test -f ../README.md" > commands.txt
truncate -s-1 commands.txt
echo "$ test -f ../README.md"
echo
../integration_test < commands.txt
echo

#test case 5
echo "test -f ../names.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ test -f ../names.txt"
echo
../integration_test < commands.txt
echo

#test case 6
echo "test test_literal_tests.sh" > commands.txt
truncate -s-1 commands.txt
echo "$ test test_literal_tests.sh"
echo
../integration_test < commands.txt
echo

#test case 7
echo "test -d test_literal_tests.sh" > commands.txt
truncate -s-1 commands.txt
echo "$ test -d test_literal_tests.sh"
echo
../integration_test < commands.txt
echo

#test case 8
echo "test ls" > commands.txt
truncate -s-1 commands.txt
echo "$ test ls"
echo
../integration_test < commands.txt
echo

#test case 9
echo "test ../prototype && ls && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ test ../prototype && ls && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

#test case 10
echo "(test ../prototype && ls) && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ (test ../prototype && ls) && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

#test case 11
echo "(test ../prototype && ls && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ (test ../prototype && ls && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

#test case 12
echo "test prototype && ls && (pwd ; echo hi)" > commands.txt
truncate -s-1 commands.txt
echo "$ test prototype && ls && (pwd ; echo hi)"
echo
../integration_test < commands.txt
echo

rm commands.txt