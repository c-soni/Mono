txtFile = 'instr.txt'
binFile = 'instr.bin'
verbose = True

with open(binFile, 'rb') as bFile:
    with open(txtFile, 'w') as tFile:
        print('Processing, please wait.')
        chunk = b' '
        while chunk != b'':
            chunk = bFile.read(2048)
            textString = ''
            for i in chunk:
                if verbose is True:
                    print(i)
                textString += '{0:x}\n'.format(i)
            tFile.write(textString)

print('Done.')