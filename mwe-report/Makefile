PDF = index.pdf
MAIN = main
FLAGS = -shell-escape
CC = pdflatex

all:
	make bib

$(PDF) : $(MAIN).tex *.tex report/*.tex
	$(CC) $(FLAGS) $<
	$(CC) $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

bib: $(MAIN).tex *.tex report/*.tex
	$(CC) $(FLAGS) $<
	bibtex $(MAIN).aux
	$(CC) $(FLAGS) $<
	$(CC) $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

biber: $(MAIN).tex *.tex report/*.tex
	$(CC) $(FLAGS) $<
	biber $(MAIN).bcf
	$(CC) $(FLAGS) $<
	$(CC) $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

clean:
	-rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml
	-cd report && rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml

.PHONY: clean, bib
