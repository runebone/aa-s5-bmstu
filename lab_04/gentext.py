from faker import Faker

f = Faker("ru")
kb = 1024

with open("file.txt", "w") as file:
    file.write(f.text(max_nb_chars=100*kb))
