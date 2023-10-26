PDF = index.pdf
MAIN = main
FLAGS = -shell-escape

all:
	make bib

$(PDF) : $(MAIN).tex *.tex report/*.tex
	pdflatex $(FLAGS) $<
	pdflatex $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

bib: $(MAIN).tex *.tex report/*.tex
	pdflatex $(FLAGS) $<
	bibtex $(MAIN).aux
	pdflatex $(FLAGS) $<
	pdflatex $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

biber: $(MAIN).tex *.tex report/*.tex
	pdflatex $(FLAGS) $<
	biber $(MAIN).bcf
	pdflatex $(FLAGS) $<
	pdflatex $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

clean:
	-rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml
	-cd report && rm  *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml

.PHONY: clean, bib
