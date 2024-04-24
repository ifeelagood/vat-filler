# Testing

## Test 1 - Different Resin Conductivity

### Controled Variables

these variables will change the analog readings. thus we must control them to get accurate and reliable tests.

|variable|unit|method|
|--------|----|------|
|electrode diameter|mm|use same ones|
|electrode distance|mm|made 3d model|
|electrode depth|mm|made 3d model,conduct test in beaker|
|analog ref voltage|V|LM7805|
|divider resistence|ohm|1 megaohm resistor|
|measurement period|ms|same in code, include ms since test start|

- electrodes must be placed in parallel, such that at any given vertical point the distance between electrodes remains the same


### Independent Variable 
Resin Type

### Dependent Variable
Analog Reading

### Test Params

electrode diameter - 1.5mm
electrode distance - 4.0mm (from centre of electrodes)
divider resistance - 1m ohm
measurement period - 250ms
number of measurements - 200
test apparatus depth - 50ml (not accounting for displacement of apparatus and electrodes!)

### Test Methodology

Do 3 trials per resin. replace resin each trial (but dont bother washing until resin change).

wash with IPA and dry when switching resin.

to measure, configure read_serial.sh, plug in, wait 5 seconds and run

`F=results/resin0x.csv; echo -n > $F; scripts/read_serial.sh | tee $F`

after PERIOD * MEASUREMENTS, it will stop. control-c, unplug and do another measurement. 


