import matplotlib.pyplot as plt
import numpy as np


#load in the csv data

# def plot_graphs_threads(num_threads):

#     num_str = str(num_threads)
#     data = np.genfromtxt('new_output_t' + num_str + '.csv', delimiter=',', skip_header=1)
#     x1 = data[:,0]
#     x2 = data[:,1]
#     x3 = data[:,2]
#     y1 = data[:,3]

#     plt.plot(x3, y1)
#     plt.xlabel('# operations')
#     plt.ylabel('time (s)')
#     plt.title('Time vs # operations with ' + num_str + ' threads')
    
#     # Save the plot as image
#     plt.savefig('plot_fix_threads_' + num_str + '.png')
    
#     #reset plot
#     plt.clf()

def plot_all_graphs():
    nums = [1, 2, 4, 8, 16, 128, 256, 512, 1024]
    
    for num in nums:
        #line graph with all the threads
        num_str = str(num)
        data = np.genfromtxt('big_output_t' + num_str + '.csv', delimiter=',', skip_header=1)
        x1 = data[:,0]
        x2 = data[:,1]
        x2 = [x * x * x for x in x2]
        x3 = data[:,2]
        y1 = data[:,3]

        plt.plot(x2, y1)
        
        
        
        #add key
    plt.legend(['1 thread', '2 threads', '4 threads', '8 threads', '16 threads', '128 threads', '256 threads', '512 threads', '1024 threads'])
    plt.xlabel('# operations')
    plt.ylabel('time (s)')
    plt.title('Time vs # operations with varying threads')
    plt.savefig('plot_fix_threads_all.png')
    plt.clf()



# Defining main function
def main():
    plot_all_graphs()


# Using the special variable 
# __name__
if __name__=="__main__":
    main()