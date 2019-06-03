<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.2.3" name="Little_Girl" tilewidth="18" tileheight="34" tilecount="24" columns="12">
 <image source="../sprites/Little_Girl.png" width="218" height="72"/>
 <tile id="0" type="12">
  <properties>
   <property name="speed" type="int" value="7"/>
  </properties>
  <objectgroup draworder="index">
   <object id="1" name="pivot" x="10" y="30" width="1" height="1"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="1" duration="100"/>
  </animation>
 </tile>
 <tile id="1" type="4">
  <animation>
   <frame tileid="1" duration="170"/>
  </animation>
 </tile>
 <tile id="3" type="9">
  <properties>
   <property name="speed" type="int" value="7"/>
  </properties>
  <animation>
   <frame tileid="3" duration="100"/>
   <frame tileid="4" duration="100"/>
   <frame tileid="5" duration="100"/>
   <frame tileid="4" duration="100"/>
  </animation>
 </tile>
 <tile id="4" type="1">
  <animation>
   <frame tileid="4" duration="100"/>
  </animation>
 </tile>
 <tile id="6" type="14">
  <properties>
   <property name="speed" type="int" value="7"/>
  </properties>
  <animation>
   <frame tileid="6" duration="100"/>
   <frame tileid="7" duration="100"/>
   <frame tileid="8" duration="100"/>
   <frame tileid="7" duration="100"/>
  </animation>
 </tile>
 <tile id="7" type="6">
  <animation>
   <frame tileid="7" duration="100"/>
  </animation>
 </tile>
 <tile id="9" type="10">
  <properties>
   <property name="speed" type="int" value="7"/>
  </properties>
  <animation>
   <frame tileid="9" duration="100"/>
   <frame tileid="10" duration="100"/>
   <frame tileid="11" duration="100"/>
   <frame tileid="10" duration="100"/>
  </animation>
 </tile>
 <tile id="10" type="2">
  <animation>
   <frame tileid="10" duration="100"/>
  </animation>
 </tile>
 <tile id="15" type="8">
  <properties>
   <property name="speed" type="int" value="7"/>
  </properties>
  <animation>
   <frame tileid="15" duration="100"/>
   <frame tileid="16" duration="100"/>
   <frame tileid="17" duration="100"/>
   <frame tileid="16" duration="200"/>
  </animation>
 </tile>
 <tile id="16" type="0">
  <animation>
   <frame tileid="16" duration="100"/>
  </animation>
 </tile>
</tileset>
