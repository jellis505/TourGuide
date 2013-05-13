.PHONY: clean

UNAME := $(shell uname)

paper: *.tex *.jpg
	pdflatex TourDruid
	bibtex TourDruid
	pdflatex TourDruid
	pdflatex TourDruid

ifeq ($(UNAME), Linux)
	gnome-open TourDruid.pdf
else
	open TourDruid.pdf
endif

clean:
	-rm -f *.aux *.log *.pdf *.synctex.gz *~ *.out