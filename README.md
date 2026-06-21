# SNES to NeoGeo Controller Adapter - Support material and code extension (SNES-to-NeoGeo-EX)

Supporting materials for Robin Edwards' ["SNES for NeoGeo" DIY Project](<https://github.com/robinhedwards/SNES-to-NeoGeo>) by [RetroCityRansom](https://www.youtube.com/@RetroCityRansom/playlists).

## About

The goal of this repository is to provide useful information for replicating Robin Edwards’ SNES-to-Neo Geo adapter. Additionally, you will find several small extensions to the original code that allow you to enable autofire, adjust the autofire speed, and swap the A and B button mappings.

All credit for the original code, the excellent 3D-printed enclosure, and the practical concept in general goes to the creator, Robin Edwards.

This repository merely represents my own small extension of the project, intended to assist with implementation and to document several modifications that I personally felt compelled to add. I think it is possible to build this adapter for less than 15€, but of course that'll depend when and where you buy all the parts, etc.. I want to mention here that there is another alternative DIY SNES to NeoGeo controller adapter option (by @Arthrimus + @Frank_fjs, check it out [HERE](https://www.arcade-projects.com/threads/snes-to-neo-geo-controller-adapters.11195/)). And of course, you could always buy a ready-made adapter like the SNES2Neo — but where’s the DIY fun then? :-)

If you are also interested in building a similar adapter for the TurboGrafx-16 / PC Engine, you can find a corresponding implementation over at my [SNEngine repository](https://github.com/retrocityransom/snengine).

## Features

- Code changes
  - Added autofire extension: L = Autofire toggle for button A, R = Autofire toggle for button B.
  - The autofire rate can be changed using hotkeys.
  - The mapping of A and B can be switched by using a hotkey combination.
  - Changes to the settings for turbofire and the A/B mapping can be saved as default.
- Diagrams, photos, bill of materials and suggestions for additional electronic components

### Button mapping

![Button mapping changes](media/snestoneogeo_button_mapping_changes_small.png)

### Hotkeys

- **SELECT + UP** => Cycle through three autofire speed settings. Experimental, but seems to work okay for most cases.
- **SELECT + DOWN** => Swaps buttons A and B
- **SELECT + RIGHT** => Save settings (the internal LED will blink a few times as visual feedback)

## Disclaimer

Use at your own risk. I am not an electrician and strongly advise against trying this without consulting a qualified professional and verifying the accuracy of all information provided in this repository.
The adapter has not been thoroughly tested yet. You may need to add resistors, capacitors or other electrical parts to ensure safe and error free operation.
The pictures provided here are not an implementation manual, but rather a personal photo diary.

## Shopping list, software & tools

Below BOM only consists of stuff I've actually used during the implementation.

| **Type** | **Optional** | **Part**                                                                                                                                                                      | **Remark**                                                                                                                                                                                                                                     |
| -------- | ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Part     |              | Arduino Pro Mini                                                                                                                                                              | Split the SNES controller signal stream into discrete signals per button. Costs around 3€-5€.                                                                                                                                                  |
| Part     |              | Male SNES controller port (like the one in the console)                                                                                                                       | Guess … Should not cost more than 50 cents rather 35 cents.                                                                                                                                                                                    |
| Part     |              | NeoGeo controller cable (15-pin) with female plug                                                                                                                             | To connect the adapter to the NeoGeo. Should cost between 5€ and 10€.                                                                                                                                                                          |
| Part     |              | Some wires & heat shrink tubing                                                                                                                                               | I've used 28 AWG wires, 30 AWG should also be fine                                                                                                                                                                                             |
| Part     | Yes          | 100uF electrolytic capcitor                                                                                                                                                   | Recommended! Mind the correct polarity! Use together with 100nF ceramic cap to smooth out electrical spikes and stabilize voltage when using 2.4gHz or BT adapters instead of a wired SNES pad. Connect between GND and VCC of SNES male port. |
| Part     | Yes          | 100nF ceramic capcitor (type 104)                                                                                                                                             | Recommended! Use together with 100uF ceramic cap to smooth out electrical spikes and stabilize voltage when using 2.4gHz or BT adapters instead of wired SNES pad. Connect between GND and VCC of SNES male port.                              |
| Part     | Yes          | 100nF ceramic capcitor (type 104) for the Ardu                                                                                                                                | Optionally put this between GND and VCC of the Arduino.                                                                                                                                                                                        |
| Part     | Yes          | (2x) Screw terminal block (12 pin) connectors 2.54mm                                                                                                                          | Very convenient if you do not want to take the risk soldering the wrong cables to your Arduino. Any size will work, but two twelve-terminal connectors are optimal.                                                                            |
| Part     | Yes          | Superglue                                                                                                                                                                     | To firmly attach the SNES port to the case. Best only glue the lower part of the case and the SNES connector, so you can still open the case without breaking it.                                                                              |
| Part     | Yes          | Adhesive Tape                                                                                                                                                                 | Wrap around the Arduino and the cables to secure them.                                                                                                                                                                                         |
| Part     | Yes          | The 3d printed SNES-TO-NEOGEO shell                                                                                                                                           | To achieve greatness!!!                                                                                                                                                                                                                        |
| Part     | Yes          | (6x) 3mmx16mm screws                                                                                                                                                          | To assemble the shell and for the strain relief.                                                                                                                                                                                               |
| Part     | Yes          | Cable/strain relief                                                                                                                                                           | I've got mine from another electrical case.                                                                                                                                                                                                    |
| Software |              | The [original SNES to NeoGeo code](https://github.com/robinhedwards/SNES-to-NeoGeo) or the [slightly enhanced code with autofire and A/B-button switching option](files/code) |                                                                                                                                                                                                                                                |
| Software |              | Arduino IDE                                                                                                                                                                   |                                                                                                                                                                                                                                                |
| Software | Yes          | [SNES to NeoGeo cheat sheet](files/SNES_to_NeoGeo_Cheat_Sheet_Example.ods)                                                                                                    | A Libre Office Workook (should also work in Excel and Open Office) to keep track of wire colors, etc..                                                                                                                                         |
| Software | Yes          | [Robin's 3d printing files](files/3d_printing_files/)                                                                                                                         | For the case. Highly recommended.                                                                                                                                                                                                              |
| Tool     |              | Soldering equipment                                                                                                                                                           | Guess ...                                                                                                                                                                                                                                      |
| Tool     |              | USB-to-TTL serial adapter, e.g. IDUINO FT232                                                                                                                                  | To program the Arduino. Make sure you have set the correct voltage for your Arduino Pro Mini on this device.                                                                                                                                   |
| Tool     | Yes          | 3d printer                                                                                                                                                                    | If you want the case ...                                                                                                                                                                                                                       |

## Wiring

[![Complete wiring](media/snestoneogeo_conn_ardu-db15-small.png)](media/snestoneogeo_conn_ardu-db15.png)

## Different DB-15 connectors

My recommendation would be to use a Neo Geo CD controller cable, such as the ones you can find [HERE](https://jammastar.com/gb/supergun/1600-scart-cable-15m.html), [HERE](https://www.arcadexpress.com/en/cables-wires/843-15-pin-snk-neogeo-aes-cd-controller-wiring-with-stripped-wires.html), or [HERE](https://de.aliexpress.com/item/1005007391821122.html). If you still have an old 15-pin serial printer cable with a female connector lying around, like the one shown in the middle picture below, that should also work. However, it will most likely not fit the Neo Geo as securely as an original Neo Geo controller cable.
In my opinion, the worst option is to use a DB15 solder-type connector that has to be assembled from separate parts (see below picture to the right hand side). The connector plug is simply too short to fit firmly into the console port and will very likely disconnect frequently. It will be okay with a NeoGeo controller extension cable though.

[![Complete wiring](media/snestoneogeo_db15-connectors_small.png)](media/snestoneogeo_db15-connectors.png)

## Assembly

(Click image to enlarge)

[![NeoGeo controller cable pinout](media/neogeo_controller_pinout_small.png)](media/neogeo_controller_pinout.png)

Find out, which cable belongs to each pin.

![Check cable colours for each pin](media/photos/snestoneogeo_assembly_10_db15_cable_check.jpg)

- Note down the cable colours per pin of the DB15 cable. Also make a note of which cable colours you want to use for the SNES pins. You can use the LibreOffice/OpenOffice Cheat Sheet (calculator workbook) to keep track of that.
- The workbook already has the correct wiring information per SNES/Arduino/DB15 pin, you just have to add the matching colors.
- Below is an example of the completed cheat sheet, which you can download from this repository. The wire colors of your DB15 cable will likely differ; therefore, clear the color values ​​and measure your own cable to determine which wire color corresponds to which pin.
  - If you use the cheat sheet to connect the DB15 cable to the Arduino, focus exclusively on columns F and G.
  - To connect the SNES connector to the Arduino, refer to columns C and G.

![Cheat sheet focus areas](media/snestoneogeo_cheat_sheet_focus_area_db15.png)


![Cheat sheet focus areas](media/snestoneogeo_cheat_sheet_focus_area_snes.png)

Soldering the screw terminal blocks to the Ardu makes it reusable for other purposes. Instead of soldering, you can now screw the wires to the correct pin. If you make a mistake, it is no longer a problem, as it can easily be corrected. The wires were not cut to the correct length and are therefore slightly too long, but that was not a problem at all.

![snestoneogeo_assembly_25.jpg](media/photos/snestoneogeo_assembly_25.jpg)

Instead of cutting off the unused wires of the DB15 cable, I insulated them with heat-shrink tubing. You never know (^_^).

![snestoneogeo_assembly_26.jpg](media/photos/snestoneogeo_assembly_26.jpg)

A 100nF ceramic capacitor between VCC and GND can help, but is not strictly necessary.

![snestoneogeo_assembly_27.jpg](media/photos/snestoneogeo_assembly_27.jpg)

Adhesive tape helps to keep everything reasonably secure in place. This makes it easier to fit everything into the case. I did not want to cut the DB15 cable at all, so it looks a bit chaotic. It's surely not best practive, but it reduced the effort to build this thing and the cable can be reused.

![snestoneogeo_assembly_28.jpg](media/photos/snestoneogeo_assembly_28.jpg)

The SNES controller connector with a 100nF ceramic and a 100uF electrolytic cap soldered to it.

![snestoneogeo_assembly_40.jpg](media/photos/snestoneogeo_assembly_40.jpg)

![snestoneogeo_assembly_41.jpg](media/photos/snestoneogeo_assembly_41.jpg)

Since I didn't want to cut the DB15 cable, I had to tuck the thick end of the cable underneath the Arduino. As a result, I had to mount the Arduino lengthwise in the case rather than crosswise. It’s a bit of a tight fit, but it still worked for me.

![snestoneogeo_assembly_80.jpg](media/photos/snestoneogeo_assembly_70.jpg)

It just barely fits :-)

![snestoneogeo_assembly_81.jpg](media/photos/snestoneogeo_assembly_71.jpg)

![snestoneogeo_assembly_82.jpg](media/photos/snestoneogeo_assembly_72.jpg)

Just as a first showcase .... The SNES connector has not been glued to the bottom part of the shell and the final touches (logo plate, spraypaint) are still missing.

![snestoneogeo_assembly_90.jpg](media/photos/snestoneogeo_assembly_80.jpg)

![snestoneogeo_assembly_95.jpg](media/photos/snestoneogeo_assembly_85.jpg)

A little spraypaint is always nice to have ...

![snestoneogeo_assembly_95.jpg](media/photos/snestoneogeo_assembly_90.jpg)

![snestoneogeo_assembly_95.jpg](media/photos/snestoneogeo_assembly_91.jpg)

![snestoneogeo_assembly_95.jpg](media/photos/snestoneogeo_assembly_92.jpg)

![snestoneogeo_assembly_95.jpg](media/photos/snestoneogeo_assembly_93.jpg)