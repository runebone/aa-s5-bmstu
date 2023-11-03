PDF = index.pdf
MAIN = main
FLAGS = -shell-escape
CC = pdflatex

all:
	make bib

$(PDF) : $(MAIN).tex *.tex report/*.tex
	-$(CC) $(FLAGS) $<
	-$(CC) $(FLAGS) $<
	-mv $(MAIN).pdf $(PDF)
	make movebib

bib: $(MAIN).tex *.tex report/*.tex
	-$(CC) $(FLAGS) $<   > /dev/null
	-bibtex $(MAIN).aux  > /dev/null
	-$(CC) $(FLAGS) $<   > /dev/null
	-$(CC) $(FLAGS) $<   > /dev/null
	-mv $(MAIN).pdf $(PDF)
	make movebib

# biber: $(MAIN).tex *.tex report/*.tex
# 	$(CC) $(FLAGS) $<
# 	biber $(MAIN).bcf
# 	$(CC) $(FLAGS) $<
# 	$(CC) $(FLAGS) $<
# 	mv $(MAIN).pdf $(PDF)

movebib:
	-mkdir -p out > /dev/null
	-mv *.aux *.log *.out *.toc *.bbl *.blg out > /dev/null
	-cd report && mv *.aux ../out > /dev/null

clean:
	-rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml > /dev/null
	-cd report && rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml > /dev/null
	rm -rf out

.PHONY: clean, bib, movebib
