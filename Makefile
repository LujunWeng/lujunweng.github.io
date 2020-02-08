SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = .
.DEFAULT_GOAL = html

html: Makefile
	@$(SPHINXBUILD) "$(SOURCEDIR)" "$(BUILDDIR)"
