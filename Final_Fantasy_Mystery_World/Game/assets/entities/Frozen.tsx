<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.2.3" name="Frozen" tilewidth="18" tileheight="34" tilecount="525" columns="35">
 <properties>
  <property name="attack_power" type="int" value="50"/>
  <property name="experience" type="int" value="300"/>
  <property name="live" type="int" value="450"/>
 </properties>
 <image source="../sprites/Frozen.png" width="641" height="524"/>
 <tile id="0">
  <objectgroup draworder="index">
   <object id="1" name="pivot" x="9.25" y="28.5625" width="1" height="1"/>
  </objectgroup>
 </tile>
 <tile id="319">
  <animation>
   <frame tileid="319" duration="200"/>
   <frame tileid="321" duration="200"/>
   <frame tileid="323" duration="200"/>
   <frame tileid="325" duration="200"/>
  </animation>
 </tile>
</tileset>
