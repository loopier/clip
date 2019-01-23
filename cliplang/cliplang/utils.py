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

def printableList(alist, target="", iter=0):
    """Returns a string representing the list in a printable format
    with nested objects tabulated"""
    s = "\n"

    if target == "clip":
        target = "<clipname>"

    i = 0
    while i < len(alist):
        n=0
        while n < iter:
            s += "\t"
            n += 1
        if type(alist[i]) == list:
            s += printableList(alist[i], alist[i-1], iter+1)
        else:
            s += alist[i] + " " + target + "\n"
        i += 1
    s += "\n"
    return s
