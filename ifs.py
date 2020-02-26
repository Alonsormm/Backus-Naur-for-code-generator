import random

s = "iCtSA"
a = ";eS"

d = s
maximo = 1000
print("Tenemos que S - > " + s)
print("Tenemos que a - > " + a + "|" + str(chr(1013)))
print("Comenzamos con: ")
print(s)
cadenaFinal = ""


def generarCadena(cadena, tam, max):
    if tam == maximo:
        global cadenaFinal
        cadenaFinal = cadena
        return
    i = len(cadena)-1
    while(i > 0):
        if cadena[i] == "A":
            print("Sustituyendo a A por ", end="")
            if random.randint(0, 1):
                temp = cadena[:i] + "(" + a + ")" + cadena[i+1:]
                # print(a)
                # print(temp)
                generarCadena(temp, tam+1, max)
                return
            if(tam == 0):
                temp = cadena[:i]
                # print("Epsilon")
                #print(temp+str(chr(1013)) + "->")
                # print(temp)
                generarCadena(temp, tam+1, max+1)
                return
            temp = cadena[:i] + cadena[i+1:]
            tempEpsilon = cadena[:i] + str(chr(1013)) + cadena[i+1:]
            # print("Epsilon")
            #print(tempEpsilon + "->")
            # print(temp)
            generarCadena(temp, tam+1, max+1)
            return
        if cadena[i] == "S":
            #print("Sustituyendo a S")
            temp = cadena[:i] + "(" + s + ")" + cadena[i+1:]
            # print(temp)
            generarCadena(temp, tam+1, max)
            return
        i -= 1


generarCadena(s, 0, 0)
cadenaIfs = ""
tabulaciones = 0
fil = open("ifs.txt", "w")

for i in cadenaFinal:
    if i == "i":
        cadenaIfs += "\t" * (tabulaciones) + "if"
    elif i == "C":
        cadenaIfs += "(C)"
    elif i == "t":
        tabulaciones += 1
        cadenaIfs += "{\n"
    elif i == ";":
        tabulaciones -= 1
        cadenaIfs += "\n" + "\t" * (tabulaciones) + "}"
    elif i == "e":
        cadenaIfs += "\n" + "\t" * (tabulaciones) + "else{\n"
        tabulaciones += 1
    elif i == ")":
        tabulaciones -= 1
        cadenaIfs += "\n" + "\t" * (tabulaciones) + "}"
        if(tabulaciones == 0):
            break

'''
for i in cadenaFinal:
    if i == "i":
        fil.write("\t" * (tabulaciones) + "if")
    elif i == "C":
        fil.write("(C)")
    elif i == "t":
        tabulaciones += 1
        fil.write("{\n")
    elif i == ";":
        tabulaciones -= 1
        fil.write("\n" + "\t" * (tabulaciones) + "}")
    elif i == "e":
        fil.write("\n" + "\t" * (tabulaciones) + "else{\n")
        tabulaciones += 1
    elif i == ")":
        tabulaciones -= 1
        fil.write("\n" + "\t" * (tabulaciones) + "}")
        if(tabulaciones == 0):
            break

fil.write(cadenaIfs)'''
fil.close()
