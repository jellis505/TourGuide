import sys, math


if __name__ == "__main__":
    
    print "Get Here"
    filename = sys.argv[1];

    #open the file
    f = open(filename,'r');
    lines = f.readlines();
    
    NN_1 = [];
    NN_3 = [];
    NN_10 = [];
    for line in lines:
        line = line.rstrip('\n');
        if line[0:2] == '1-':
            split_line = line.split(': ');
            oneiter = float(split_line[1]);
            NN_1.append(oneiter);
        if line[0:2] == '3-':
            split_line = line.split(': ');
            oneiter = float(split_line[1]);
            NN_3.append(oneiter);
        if line[0:2] =='10':
            split_line = line.split(': ');
            oneiter = float(split_line[1]);
            NN_10.append(oneiter);

    #Now calculate te accuracies
    nn_acc_1 = sum(NN_1)/float(len(NN_1));
    nn_acc_3 = sum(NN_3)/float(len(NN_3));
    nn_acc_10 = sum(NN_10)/float(len(NN_10));

    #OUtput to the screen
    print "This is 1 NN accuracy: ", nn_acc_1;
    print "This is 3 NN accuracy: ", nn_acc_3;
    print "This is 10 NN accuracy: ", nn_acc_10;

