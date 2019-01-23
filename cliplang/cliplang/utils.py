def printableDictionary(dict, iter=0):
    """Returns a string representing the dictionary in a printable format
    with nested objects tabulated"""
    s = "\n"
    for k in dict:
        i=0
        while i < iter:
            s += "\t"
            i += 1
        if type(dict[k]) == type(dict):
            s += k + ":" + printableDictionary(dict[k], iter+1)
        else:
            s += k + ": " + dict[k] + "\n"
    return s

def printableList(alist, iter=0):
    """Returns a string representing the list in a printable format
    with nested objects tabulated"""
    s = "\n"

    for k in alist:
        i=0
        while i < iter:
            s += "\t"
            i += 1
        if type(k) == list:
            s += printableList(k, iter+1)
        else:
            s += k + "\n"
    s += "\n"
    return s
