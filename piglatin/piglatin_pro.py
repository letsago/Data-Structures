# a piglatin translator where input must have no more than 1 punctuation per word, no more
# than one space between words, and all words' first 2 characters must either be a vowel or a consonant

vowels = "aeiouAEIOU"
consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
valid_chars = vowels + consonants + " "
punctuation = ".?!,;:"
invalid_chars = "1234567890~@#$%^&*()-+_=[{|'<>/\}]"

# index_spaces function will return a list of indices in a sentence that are spaces
def index_spaces(sentence):
    space_index = [-1] # introduce psuedo-space which will allow operations on first word
    for i in range(len(sentence)):
        if sentence[i] == " ":
            space_index.append(i)
    return space_index

# takes in sentence from user with appropriate restrictions
def user_input():
    sentence = input("Please enter a sentence: ")
    space_index = index_spaces(sentence)
    consecutive_space_counter = 0
    for i in range(len(space_index)):
        punctuation_counter = 0
        if space_index[i] != max(space_index):
            for char in sentence[space_index[i]+1: space_index[i+1]]:
                if char in punctuation:
                    punctuation_counter = punctuation_counter + 1
        if space_index[i] == max(space_index):
            for char in sentence[space_index[i]+1: len(sentence)]:
                if char in punctuation:
                    punctuation_counter = punctuation_counter + 1
        if punctuation_counter > 1:
            print("SENTENCE INVALID: TOO MUCH INAPPROPRIATE PUNCTUATION")
            return
    for i in range(len(space_index)):
        if sentence[space_index[i] + 1] not in valid_chars or sentence[space_index[i] + 2] not in valid_chars:
            print("SENTENCE INVALID: PLEASE TYPE IN VALID WORDS")
            return
        if space_index[i] == consecutive_space_counter + 1:
            print("SENTENCE INVALID: PLEASE KEEP ONE SPACE BETWEEN WORDS")
            return
        consecutive_space_counter = space_index[i]
    return sentence

# returns an index list of capitalized words  
def check_capital_words(sentence, space_index):
    capital_words_index = []
    word_counter = 0
    for index in space_index:
        if sentence[index + 1].isupper():
            capital_words_index.append(word_counter)
            word_counter = word_counter + 1
        if not sentence[index + 1].isupper():
            word_counter = word_counter + 1
    return capital_words_index

# returns list of word beginning and ending indices within sentence
def define_word_indices(sentence, space_index):
    all_word_indices = []
    word_begin_index = 0
    word_end_index = 0
    for i in range(len(space_index)):
        ind_word_indices = []
        word_begin_index = space_index[i] + 1
        ind_word_indices.append(word_begin_index)
        if len(space_index) > 1:
            if space_index[i] != max(space_index):
                word_end_index = space_index[i+1] - 1
            if space_index[i] == max(space_index):
                word_end_index = len(sentence) - 1
        if len(space_index) == 1:
            word_end_index = len(sentence) - 1
        ind_word_indices.append(word_end_index)
        all_word_indices.append(ind_word_indices)
    return all_word_indices

# returns fully transformed new sentence by adding splices of original sentence in appropriate order
def piglatin_transform(sentence, word_indices):
    new_sentence = ""
    for indices in word_indices:
        if sentence[indices[0]] in vowels:
            if sentence[indices[1]] in punctuation:
                new_sentence = new_sentence + sentence[indices[0]:indices[1]] + "ay" + sentence[indices[1]] + " "
            if sentence[indices[1]] not in punctuation:
                new_sentence = new_sentence + sentence[indices[0]:indices[1] + 1] + "ay "
        if sentence[indices[0]] in consonants and sentence[indices[0] + 1] in vowels:
            if sentence[indices[1]] in punctuation:
                new_sentence = new_sentence + sentence[indices[0] + 1:indices[1]] + sentence[indices[0]] + "ay" + sentence[indices[1]] + " "
            if sentence[indices[1]] not in punctuation:
                new_sentence = new_sentence + sentence[indices[0] + 1:indices[1] + 1] + sentence[indices[0]] + "ay "
        if sentence[indices[0]] in consonants and sentence[indices[0] + 1] in consonants:
            if sentence[indices[1]] in punctuation:
                new_sentence = new_sentence + sentence[indices[0] + 2:indices[1]] + sentence[indices[0]:indices[0] + 2] + "ay" + sentence[indices[1]] + " "
            if sentence[indices[1]] not in punctuation:
                new_sentence = new_sentence + sentence[indices[0] + 2:indices[1] + 1] + sentence[indices[0]:indices[0] + 2] + "ay "                
    return new_sentence.lower()

# capitalizes appropriate words within pig latin transformed based on capital words indices within sentence 
def capitalize(sentence, space_index, capital_words_index):
    new_sentence = ""
    updated_counter = 0
    if len(capital_words_index) == 0:
        return sentence
    for index in capital_words_index:
        if index == max(capital_words_index):
            new_sentence = new_sentence + sentence[updated_counter:space_index[index] + 1] + sentence[space_index[index] + 1].upper() + sentence[space_index[index] + 2:]
        if index != max(capital_words_index):
            new_sentence = new_sentence + sentence[updated_counter:space_index[index] + 1] + sentence[space_index[index] + 1].upper()
        updated_counter = space_index[index] + 2
    return new_sentence

def main():
    # collect appropriate information before pig latin transformation
    sentence = user_input()
    space_index = index_spaces(sentence)
    capital_words_index = check_capital_words(sentence, space_index)
    word_indices = define_word_indices(sentence, space_index)
    
    # pig latin transformation
    new_sentence = piglatin_transform(sentence, word_indices)

    # capitalize appropriate words post transformation to preserve word capitalization within original sentence
    space_index = index_spaces(new_sentence)
    newest_sentence = capitalize(new_sentence, space_index, capital_words_index)

    print(newest_sentence)

main()