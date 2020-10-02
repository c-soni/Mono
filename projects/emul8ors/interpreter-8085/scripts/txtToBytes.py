txtFile = 'instr.txt'
binFile = 'instr.bin'
verbose = False

with open(txtFile, 'r') as tFile:
    with open(binFile, 'wb') as bFile:
        print('Processing, please wait.')
        for line in tFile:
            bytestring = b''
            instructions = line.split()
            for i in instructions:
                i = i.strip()
                if verbose is True:
                    print(i)
                bytestring += bytes.fromhex(i)
            bFile.write(bytestring)

print('Done.')