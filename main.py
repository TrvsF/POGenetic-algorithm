from tokenize import Double
import matplotlib.pyplot as plt

def plot():
    methodOData = []
    methodOGen = []
    methodOTotFitness = []
    methodOBestFitness = []
    methodOAvgFitness = []
    methodOWorstFitness = []

    methodTData = []
    methodTGen = []
    methodTTotFitness = []
    methodTBestFitness = []
    methodTAvgFitness = []
    methodTWorstFitness = []

    gName = "gene-2022-05-02_20-27-17"

    with open(gName+'.txt', 'r+') as file:
        for line in file:
            if line[0] == '-':
                if (next(file)[0] == '0'):
                    methodOGen.append(float(next(file).strip('\n')))
                    methodOTotFitness.append(float(next(file).strip('\n')))
                    methodOBestFitness.append(float(next(file).strip('\n')))
                    methodOAvgFitness.append(float(next(file).strip('\n')))
                    methodOWorstFitness.append(float(next(file).strip('\n')))
                else:
                    methodTGen.append(float(next(file).strip('\n')))
                    methodTTotFitness.append(float(next(file).strip('\n')))
                    methodTBestFitness.append(float(next(file).strip('\n')))
                    methodTAvgFitness.append(float(next(file).strip('\n')))
                    methodTWorstFitness.append(float(next(file).strip('\n')))

    plt.scatter(methodOGen, methodOBestFitness)
    plt.scatter(methodTGen, methodTBestFitness)
    plt.xlabel("generation")
    plt.ylabel("fitness")       
    plt.show()
            
if __name__ == "__main__":
    print("starting")
    plot()