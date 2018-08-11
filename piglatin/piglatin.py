# a piglatin translator

vowels = "aeiouAEIOU"
consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
alphabet_chars = vowels + consonants
punctuation = ".?!,"
valid_chars = alphabet_chars + punctuation + "-" + "'"

# returns user input string
def user_input():
    sentence = input("Please enter your input: ")
    return sentence

# operation on sentence that adds space between punctuation and valid_char and returns string
def add_space_after_punctuation(word):
    new_word = ""
    for i in range(len(word) - 1): # checks all chracters except for last to avoid index out of range errors
        if word[i] in punctuation and word[i + 1] in alphabet_chars:
            new_word = new_word + word[i] + " "
        else:
            new_word = new_word + word[i]
    new_word = new_word + word[len(word) - 1] # must add last character of original input
    return new_word

# splits string into list of words and returns that list 
def string_split(sentence):
    word_list = sentence.split(" ")
    return word_list

# transforms each word of string input into pig latin
def pig_latin_transform(word):
    if word == "":
        return word
    new_word = ""
    first_index = 0                     # first_index is used to splice out which characters to move to end of word
    last_index = len(word)              # last_index is used to reference where to move first_index characters and add remaining transform characters + punctuation
    for i in range(len(word)):          # first checks that if invalid characters exist, no transform
        if word[i] not in valid_chars: 
            return word
    for i in range(len(word)):          # then counts number of characters before first vowel or dash
        if word[i] in consonants:
            first_index = first_index + 1
        if word[i] in vowels or word[i] == "-":
            break
    for i in reversed(range(len(word))):# counts number of characters in reverse that is punctuation
        if word[i] in punctuation:
            last_index = last_index - 1
        else:
            break
    if first_index > 0:                 # if word contains consonants before first vowel or -
        new_word = word[first_index:last_index] + word[:first_index] + "ay" + word[last_index:]
    if first_index == 0:                # if word starts with vowel or -
        new_word = word[:last_index] + "yay" + word[last_index:]
    newest_word = new_word
    if word[0].isupper():               # capitalizes new word if old word is capitalized
        newest_word = new_word[0].upper() + new_word[1:].lower()
    return newest_word

# joins list of words into a string
def string_join(word_list):
    final_sentence = " ".join(word_list)
    return final_sentence

# returns complete pig latin translation
def return_translation(sentence):
    new_sentence = add_space_after_punctuation(sentence)
    word_list = string_split(new_sentence)
    new_word_list = []
    for word in word_list:
        new_word_list.append(pig_latin_transform(word))
    final_sentence = string_join(new_word_list)
    return final_sentence

def main():
    sentence = user_input()
    new_sentence = return_translation(sentence)
    print(new_sentence)

main()

def test_answer():
    assert return_translation("I like pie.") == "Iyay ikelay iepay."
    assert return_translation("x-ray") == "-rayxay"
    assert return_translation("Hi! I'm Patrick.") == "Ihay! I'myay Atrickpay."
    assert return_translation("Oh my snotbubbles?!?!? What happened??") == "Ohyay ymay otbubblessnay?!?!? Atwhay appenedhay??"
    assert return_translation("") == ""
    assert return_translation("hi:)") == "hi:)"
    assert return_translation("bye3") == "bye3"
    assert return_translation("hi!hello?") == "ihay! ellohay?"
    assert return_translation("Yippy!  I feel great!") == "Ippyay! Iyay eelfay eatgray!"

