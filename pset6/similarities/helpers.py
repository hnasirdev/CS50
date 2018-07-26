from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    set1 = set(a.split("\n"))
    set2 = set(b.split("\n"))
    similarities = set1.intersection(set2)
    # TODO
    return similarities


def sentences(a, b):
    """Return sentences in both a and b"""
    set1 = set(sent_tokenize(a))
    set2 = set(sent_tokenize(b))
    similarities = set1.intersection(set2)
    # TODO
    return list(similarities)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    set1=set()
    set2=set()
    for i in range(len(a)-(n-1)):
        set1.add(a[i:i+n])

    for i in range(len(b)):
        set2.add(b[i:i+n])
       # set2 = set(b[i:i+n])



    similarities = set1.intersection(set2)
    # TODO
    return similarities
