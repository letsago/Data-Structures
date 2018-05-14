# -*- coding: utf-8 -*-
"""
Created on Sun May  6 20:16:37 2018

@author: 9yu6990
"""

vowels = "aeiou"
consonants = "bcdfghjklmnpqrstvwxyz"
punctuation = ".?!,;:"
invalid_symbols = "1234567890~@#$%^&*()-+_=[{|'<>/\}]"

def user_input():
    sentence = input("Please type in your input: ")
    return sentence

def str_to_char_list_transform(sentence):
    return list(sentence.lower())

def word_list(char_list):
    all_list_char = []
    list_char = []
    for elem in char_list:
        if elem != " ":
            list_char.append(elem)
        if elem == " ":
            all_list_char.append(list_char)
            list_char = []
    all_list_char.append(list_char)
    return all_list_char

def identifier(char_list):
    identifier = []
    # 0 means vowel and 1 means consonant
    for elem in char_list:
        if elem in vowels:
            identifier.append(0)
        elif elem in consonants:
            identifier.append(1)
        else:
            identifier.append('')
        
    return identifier

def pig_latin_transform_1(word, identifier):
    new_word = word
    if word[len(word) - 1] in punctuation:
        del new_word[len(word) - 1]

    for i in range(len(identifier)):
        if identifier[i] == 1:
            new_word.append(word[0])
            del new_word[0]
        if identifier[i] == 0:
            break
    return new_word
    
def pig_latin_transform_2(word):
    word.append("ay")
    ''.join(word)
    return word
    
def main():
    sentence = user_input()
    char_list = str_to_char_list_transform(sentence)
    old_master_list = word_list(char_list)
    for i in range(len(old_master_list)):
        pig_latin_transform_1(old_master_list[i], identifier(old_master_list[i]))

    

main()
    