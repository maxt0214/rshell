echo "-Inpput Redirection Tests-"
echo

#test case 1
echo "ls | tr a-z A-Z > out.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ ls | tr a-z A-Z > out.txt"
echo
echo "out.txt: "
../integration_test < commands.txt
cat out.txt
echo

#test case 2
echo "cat < out.txt | tr A-Z a-z | tee out2.txt | tr A-Z a-z > out3.txt" > commands.txt
truncate -s-1 commands.txt
echo "$ cat < out.txt | tr A-Z a-z | tee out2.txt | tr A-Z a-z > out3.txt"
echo
../integration_test < commands.txt
echo "out.txt2: "
cat out2.txt
echo "out.txt3: "
cat out3.txt
echo

#test case 3
echo "cat < out.txt | tr A-Z a-z | tee out2.txt | tr A-Z a-z > out3.txt && echo printed out" > commands.txt
truncate -s-1 commands.txt
echo "$ cat < out.txt | tr A-Z a-z | tee out2.txt | tr A-Z a-z > out3.txt && echo printed out"
echo
../integration_test < commands.txt
echo "out.txt2: "
cat out2.txt
echo "out.txt3: "
cat out3.txt
echo

rm out.txt ; rm out2.txt ; rm out3.txt
rm commands.txt