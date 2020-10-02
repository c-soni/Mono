txtFile = 'instr.txt'
binFile = 'instr.bin'
verbose = False

# tokenizes a line to remove comments and generate other tokens
def tokenize(line, tokenList):
    data = (line.split('//')[0]).strip()
    data = [x.strip() for x in data.split(',')]
    tokenList.extend(data)

# parses a file to generate a list of tokens
def parseFile(filename):
    tokenList = []
    print('Processing' + filename + ', please wait.')
    with open(filename, 'r') as f:
        for line in f:
            tokenize(line, tokenList)

    return tokenList

def consumeToken(token):
    return


# tokenList = []
# with open(txtFile, 'r') as tFile:
#     with open(binFile, 'wb') as bFile:
#         print('Processing, please wait.')
#         for line in tFile:
#             bytestring = b''
#             instructions = line.split()
#             for i in instructions:
#                 i = i.strip()
#                 i = i.strip('0x')
#                 if verbose is True:
#                     print(i)
#                 bytestring += bytes.fromhex(i)
#             bFile.write(bytestring)


# tokenize('STA,0x00,0x20   // Store Accumulator data at location 0x2000', tokenList)
print(parseFile(txtFile))
print('Done.')