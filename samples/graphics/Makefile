TARGETS := rsxtest rsxtest_spu cairo jpgtest pngtest videoTest #rsxTest rsxTestVP

all:
	@for TARGET in $(TARGETS); do $(MAKE) --no-print-directory -C $$TARGET; done

clean:
	@for TARGET in $(TARGETS); do $(MAKE) --no-print-directory -C $$TARGET clean; done
