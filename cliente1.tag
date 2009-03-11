<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>Cliente C++ - Documentacion Tecnica</title>
    <filename>index</filename>
    <docanchor file="index">intro_sec</docanchor>
  </compound>
  <compound kind="page">
    <name>spec_file_map</name>
    <title>Especificacion de formatos de mapas</title>
    <filename>spec_file_map</filename>
  </compound>
  <compound kind="struct">
    <name>Ao_MiCabecera</name>
    <filename>structAo__MiCabecera.html</filename>
    <member kind="variable">
      <type>Sint8</type>
      <name>desc</name>
      <anchorfile>structAo__MiCabecera.html</anchorfile>
      <anchor>f4e999271e7d6eb5c3d5e4f4311e9c64</anchor>
      <arglist>[255]</arglist>
    </member>
    <member kind="variable">
      <type>Sint32</type>
      <name>CRC</name>
      <anchorfile>structAo__MiCabecera.html</anchorfile>
      <anchor>ee646105d70fcf3ebecfeff2627acb7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint32</type>
      <name>MagicWord</name>
      <anchorfile>structAo__MiCabecera.html</anchorfile>
      <anchor>0a792a1571e66a63a8d2377bfa110a62</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AoGraficosInd_Header</name>
    <filename>structAoGraficosInd__Header.html</filename>
    <member kind="variable">
      <type>Ao_MiCabecera</type>
      <name>MiCabecera</name>
      <anchorfile>structAoGraficosInd__Header.html</anchorfile>
      <anchor>426b4d390e410630cff9498f9f50ee21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>tempint</name>
      <anchorfile>structAoGraficosInd__Header.html</anchorfile>
      <anchor>d9e85c255386f96ff61e0fe5ad0dc002</anchor>
      <arglist>[5]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>AoMap_Header</name>
    <filename>structAoMap__Header.html</filename>
    <member kind="variable">
      <type>Sint16</type>
      <name>MapVersion</name>
      <anchorfile>structAoMap__Header.html</anchorfile>
      <anchor>afa50b025f24ed8ea5baa825f5bac1ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Ao_MiCabecera</type>
      <name>MiCabecera</name>
      <anchorfile>structAoMap__Header.html</anchorfile>
      <anchor>070f43e3270f81e0f149968f2c15909a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>tempint</name>
      <anchorfile>structAoMap__Header.html</anchorfile>
      <anchor>1bffcc0b2cb88aafd79e226fbdb1fb99</anchor>
      <arglist>[4]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ClienteArgentum</name>
    <filename>classClienteArgentum.html</filename>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>classClienteArgentum.html</anchorfile>
      <anchor>ab3bfe57521cbfb72dc8af2ea6fcc5d2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ImageManager</name>
    <filename>classImageManager.html</filename>
    <member kind="function">
      <type></type>
      <name>ImageManager</name>
      <anchorfile>classImageManager.html</anchorfile>
      <anchor>14c7d6dbc49fd3136df4ab0b5c458e33</anchor>
      <arglist>(ga::GraphicsAdapter_ptr graphic)</arglist>
    </member>
    <member kind="function">
      <type>ga::Image_ptr</type>
      <name>getImage</name>
      <anchorfile>classImageManager.html</anchorfile>
      <anchor>cab07b4fea61c2711ec0b9e69eccaa0c</anchor>
      <arglist>(int num)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::queue&lt; int &gt;</type>
      <name>_history</name>
      <anchorfile>classImageManager.html</anchorfile>
      <anchor>b256eca6a6a1c42295f2da8973160b87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; ImageMetaData &gt;</type>
      <name>_imgs</name>
      <anchorfile>classImageManager.html</anchorfile>
      <anchor>5d07215ead3e1536713e375959b2f836</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ga::GraphicsAdapter_ptr</type>
      <name>_graphic</name>
      <anchorfile>classImageManager.html</anchorfile>
      <anchor>93c09cd52efd5f0215c8b26ef8478310</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">ImageManager::ImageMetaData</class>
  </compound>
  <compound kind="class">
    <name>RendererEngine</name>
    <filename>classRendererEngine.html</filename>
    <member kind="function">
      <type>ga::GraphicsAdapter_ptr</type>
      <name>getGraphicsAdapter</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>354ff1a4f5eaea67c17c1c8458eb0d76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ImageManager_ptr</type>
      <name>getImageManager</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>87addb80c06c3f46c8424e1364c61608</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setMap</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>694d0a81dbaa5713aa6f60602fb26459</anchor>
      <arglist>(ao::MapFile_ptr map)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>render</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>106fe01132a1d839f67e68409e8dcd34</anchor>
      <arglist>(int incX, int incY)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>beginFrame</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>a8efa9616fd78c8216396aa6ccb71351</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>endFrame</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>7ef504ce9778fe58d4e5d672d1a692a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>9c5bcbc0a6775e4e87b9500fded0ae1e</anchor>
      <arglist>(ao::GrhDataFile_ptr grhData, ga::GraphicsAdapter_ptr graphic)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>renderGrh</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>433ba1af51c106b8080ba97577ca6838</anchor>
      <arglist>(ao::GrhDataItem &amp;grhDataItem, int basePixelX, int basePixelY, bool center=false)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>renderLayerTile</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>79274b161316b31521eb12ba847440b2</anchor>
      <arglist>(int layerNum, ao::MapTile &amp;tile, int basePixelX, int basePixelY, bool center=false)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ga::GraphicsAdapter_ptr</type>
      <name>_graphic</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>9a04b5bec2926689d50c342ef4689d36</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ImageManager_ptr</type>
      <name>_imgMan</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>b05c3e2cd557a817b8945598838e4ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ao::GrhDataFile_ptr</type>
      <name>_grhData</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>b4b1ed6f2d754b450193698265ee1137</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ao::GrhManager_ptr</type>
      <name>_grhManager</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>58b2444f4aad25ac20369ee0195d4c76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ao::MapFile_ptr</type>
      <name>_map</name>
      <anchorfile>classRendererEngine.html</anchorfile>
      <anchor>628ab99020f5adbfe9f67955200e904a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RendererEngineSDL</name>
    <filename>classRendererEngineSDL.html</filename>
    <base>RendererEngine</base>
    <member kind="function">
      <type></type>
      <name>RendererEngineSDL</name>
      <anchorfile>classRendererEngineSDL.html</anchorfile>
      <anchor>561b0cc2d17b148564e9c1458f134006</anchor>
      <arglist>(ao::GrhDataFile_ptr grhData)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>beginFrame</name>
      <anchorfile>classRendererEngineSDL.html</anchorfile>
      <anchor>48c2733a81eb6f2a2651c08a76b50c83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>endFrame</name>
      <anchorfile>classRendererEngineSDL.html</anchorfile>
      <anchor>3e52b21fb3b388ef0788257ad6805461</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SDL_Surface *</type>
      <name>_screen</name>
      <anchorfile>classRendererEngineSDL.html</anchorfile>
      <anchor>dd545c868a1813a8e86b3ff56937926c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::Pos</name>
    <filename>classao_1_1Pos.html</filename>
    <member kind="function">
      <type></type>
      <name>Pos</name>
      <anchorfile>classao_1_1Pos.html</anchorfile>
      <anchor>01ab985fac96da11128505f44355706d</anchor>
      <arglist>(Uint16 xx=0, Uint16 yy=0)</arglist>
    </member>
    <member kind="variable">
      <type>Uint16</type>
      <name>x</name>
      <anchorfile>classao_1_1Pos.html</anchorfile>
      <anchor>c5fa354a71ac20ac626db9415a314a5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint16</type>
      <name>y</name>
      <anchorfile>classao_1_1Pos.html</anchorfile>
      <anchor>394c6a62de12f665c63e12b4b149592d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::GrhBasic</name>
    <filename>classao_1_1GrhBasic.html</filename>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>classao_1_1GrhBasic.html</anchorfile>
      <anchor>40e0369e0c1180df795decd296dd28c3</anchor>
      <arglist>(Sint16 _index)</arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>index</name>
      <anchorfile>classao_1_1GrhBasic.html</anchorfile>
      <anchor>afe45c338f62029d3c1f309d8db42ad3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint8</type>
      <name>frame</name>
      <anchorfile>classao_1_1GrhBasic.html</anchorfile>
      <anchor>10bad46f56c207dc6cdd81df5725a439</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint8</type>
      <name>speed</name>
      <anchorfile>classao_1_1GrhBasic.html</anchorfile>
      <anchor>03ff04de787627ff70a3550c0433d20f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint8</type>
      <name>started</name>
      <anchorfile>classao_1_1GrhBasic.html</anchorfile>
      <anchor>7ade65c6ff66751ca8aa688e04819609</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::MapTile</name>
    <filename>classao_1_1MapTile.html</filename>
    <member kind="variable">
      <type>bool</type>
      <name>blocked</name>
      <anchorfile>classao_1_1MapTile.html</anchorfile>
      <anchor>f8c8bd9e647a88cef2e7a950f79bc23b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>trigger</name>
      <anchorfile>classao_1_1MapTile.html</anchorfile>
      <anchor>688367a6e22bc995b1b724e07e51b0c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GrhBasic</type>
      <name>graphic</name>
      <anchorfile>classao_1_1MapTile.html</anchorfile>
      <anchor>df2267f1364b592250018084bca1d83d</anchor>
      <arglist>[4]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::MapFile</name>
    <filename>classao_1_1MapFile.html</filename>
    <member kind="function">
      <type>void</type>
      <name>loadMapFile</name>
      <anchorfile>classao_1_1MapFile.html</anchorfile>
      <anchor>44c82b4128e897a529ca70795b0121bb</anchor>
      <arglist>(std::string mapFile)</arglist>
    </member>
    <member kind="function">
      <type>MapTile &amp;</type>
      <name>getTile</name>
      <anchorfile>classao_1_1MapFile.html</anchorfile>
      <anchor>4e5112da7fb995c191ee6af748151566</anchor>
      <arglist>(const Pos &amp;wp)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>AnchoMapa</name>
      <anchorfile>classao_1_1MapFile.html</anchorfile>
      <anchor>b59583eb3ef14654bf2f9d3411349e8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>AltoMapa</name>
      <anchorfile>classao_1_1MapFile.html</anchorfile>
      <anchor>05b0a19e64f06794b058ae69c36e47d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::GrhDataItem</name>
    <filename>classao_1_1GrhDataItem.html</filename>
    <member kind="variable">
      <type>Sint16</type>
      <name>sx</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>871e16c381a81a2d4c47071d32b8d3df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>sy</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>12d8885761ea6b09caaeeb02e429f234</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>fileNum</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>49213e2704b9fec5de69a67546214500</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>pixelWidth</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>3ac66ad2cc90181b2906da6f60ba297b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>pixelHeight</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>b1c9e2a91905117666e2c387c0c4f060</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>tileWidth</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>85bc983d1b9f768bb070d361f264ccaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>tileHeight</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>cc25f767ebf4eed2819c5da05cb61f20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>numFrames</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>c26da788fb77b6fea0711e1c1c8051ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>speed</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>8ac748d52bea4d5658528cbcb01107c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Sint16</type>
      <name>frames</name>
      <anchorfile>classao_1_1GrhDataItem.html</anchorfile>
      <anchor>f3bde045425d5bdfc026f405d6d6aa76</anchor>
      <arglist>[25]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::GrhDataFile</name>
    <filename>classao_1_1GrhDataFile.html</filename>
    <member kind="function">
      <type>void</type>
      <name>loadData</name>
      <anchorfile>classao_1_1GrhDataFile.html</anchorfile>
      <anchor>8c43b03e73346cf1b5776e78c0695cdc</anchor>
      <arglist>(std::string dataFile)</arglist>
    </member>
    <member kind="function">
      <type>GrhDataItem &amp;</type>
      <name>getGrhData</name>
      <anchorfile>classao_1_1GrhDataFile.html</anchorfile>
      <anchor>3635701aca81176b126860d22eb2d63f</anchor>
      <arglist>(int num)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ao::GrhManager</name>
    <filename>classao_1_1GrhManager.html</filename>
    <member kind="function">
      <type></type>
      <name>GrhManager</name>
      <anchorfile>classao_1_1GrhManager.html</anchorfile>
      <anchor>2a8948b769ff08330620178cfcdfbda1</anchor>
      <arglist>(GrhDataFile_ptr grhdata)</arglist>
    </member>
    <member kind="function">
      <type>GrhDataItem &amp;</type>
      <name>getNextFrame</name>
      <anchorfile>classao_1_1GrhManager.html</anchorfile>
      <anchor>e7cc5677ef45abf1ecc262d0157593ce</anchor>
      <arglist>(GrhBasic &amp;grh)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::Color</name>
    <filename>classga_1_1Color.html</filename>
    <member kind="function">
      <type></type>
      <name>Color</name>
      <anchorfile>classga_1_1Color.html</anchorfile>
      <anchor>e60ee5f8777406e32706fd1054edc2bc</anchor>
      <arglist>(Uint8 rr, Uint8 gg, Uint8 bb, Uint8 aa=0xff)</arglist>
    </member>
    <member kind="variable">
      <type>Uint8</type>
      <name>r</name>
      <anchorfile>classga_1_1Color.html</anchorfile>
      <anchor>1fa92e207447545243facf3590db113a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint8</type>
      <name>g</name>
      <anchorfile>classga_1_1Color.html</anchorfile>
      <anchor>7404815b4c2efc34ad3960c3f344d5bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint8</type>
      <name>b</name>
      <anchorfile>classga_1_1Color.html</anchorfile>
      <anchor>4652618d87273cdd26c757788040092c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint8</type>
      <name>a</name>
      <anchorfile>classga_1_1Color.html</anchorfile>
      <anchor>f8bf9d89e382795fe44b9a9ce368b200</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::GraphicsAdapterException</name>
    <filename>classga_1_1GraphicsAdapterException.html</filename>
    <member kind="function">
      <type></type>
      <name>GraphicsAdapterException</name>
      <anchorfile>classga_1_1GraphicsAdapterException.html</anchorfile>
      <anchor>9c5bd85792328047024f4ad57168d1d5</anchor>
      <arglist>(std::string mensaje)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>what</name>
      <anchorfile>classga_1_1GraphicsAdapterException.html</anchorfile>
      <anchor>8b8e5683c1570b959bb13b09ccba0474</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::Point</name>
    <filename>classga_1_1Point.html</filename>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classga_1_1Point.html</anchorfile>
      <anchor>50989f34ede2a43d36afcbac377660d8</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_x</name>
      <anchorfile>classga_1_1Point.html</anchorfile>
      <anchor>001af322e70b8f6ada9cad8cd77c3204</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_y</name>
      <anchorfile>classga_1_1Point.html</anchorfile>
      <anchor>473e54edaa89b954fadfa38fdd399d43</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::Image</name>
    <filename>classga_1_1Image.html</filename>
    <member kind="function">
      <type>const Rect &amp;</type>
      <name>getRect</name>
      <anchorfile>classga_1_1Image.html</anchorfile>
      <anchor>fc541cb5a8a8231141ae07a1b566286e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setColorKey</name>
      <anchorfile>classga_1_1Image.html</anchorfile>
      <anchor>3460c76e15e7edf7bfe0d90913a17ca4</anchor>
      <arglist>(const Color &amp;c, bool active=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setAlpha</name>
      <anchorfile>classga_1_1Image.html</anchorfile>
      <anchor>57ef080bb1dd365839535412be39c722</anchor>
      <arglist>(unsigned int alpha, bool active=true)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>displayFormat</name>
      <anchorfile>classga_1_1Image.html</anchorfile>
      <anchor>7f1ca896bd9559ecdd147e53b1df570c</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Rect</type>
      <name>_rect</name>
      <anchorfile>classga_1_1Image.html</anchorfile>
      <anchor>94753a819429bdb8b882bb66125c898b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::GraphicsAdapter</name>
    <filename>classga_1_1GraphicsAdapter.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>drawPoint</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>2de12be8acd0b778c72b4434e514c222</anchor>
      <arglist>(int x, int y, const Color &amp;c)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>drawPoint</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>843b6809608c67be3f78d63e93a56781</anchor>
      <arglist>(const Point &amp;p, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>drawLine</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>e5d5bc8367e823f5455752734a7ec949</anchor>
      <arglist>(int x1, int y1, int x2, int y2, const Color &amp;c)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>drawLine</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>355626af4b823cd25fa089da5dc786e5</anchor>
      <arglist>(const Point &amp;p1, const Point &amp;p2, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>drawRect</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>9fee66a5cc8aedcd38255815bc7a4393</anchor>
      <arglist>(const Rect &amp;r, const Color &amp;c)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>drawRect</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>4761698c5e66068a0c5c40287951e7ac</anchor>
      <arglist>(int x, int y, int w, int h, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Image_ptr</type>
      <name>loadImage</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>6c79b49c5e2c66ea6660e27481ef4c8d</anchor>
      <arglist>(std::string imagePath)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>drawImage</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>2c00a598eed5bea7debcf2d3e304f80c</anchor>
      <arglist>(Image_ptr img, const Rect &amp;src, const Point &amp;dest)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>drawImage</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>53b253c598993ccdbc0852c8637a5f08</anchor>
      <arglist>(Image_ptr img, const Point &amp;dest)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>beginFrame</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>96bff74cb46e415aeea0924a9adc6a5b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>endFrame</name>
      <anchorfile>classga_1_1GraphicsAdapter.html</anchorfile>
      <anchor>3fde45a04fd289a3264010fe26f8d3ea</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::GraphicsAdapterSDL</name>
    <filename>classga_1_1GraphicsAdapterSDL.html</filename>
    <base>ga::GraphicsAdapter</base>
    <member kind="function">
      <type></type>
      <name>GraphicsAdapterSDL</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>2ad84ad0e8fd5cec8c4ce3bb5d6a9498</anchor>
      <arglist>(SDL_Surface *surface)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drawPoint</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>dd9c794cd222c1fda3b0a138cbdf89e8</anchor>
      <arglist>(int x, int y, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drawLine</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>0a159ddd12a60f477d1806c1abcd3d70</anchor>
      <arglist>(int x1, int y1, int x2, int y2, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drawRect</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>5269f04d9519efc52ff59f6cc355a92a</anchor>
      <arglist>(const Rect &amp;r, const Color &amp;c)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Image_ptr</type>
      <name>loadImage</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>d46a846a85eddb2246e268882f98e9e9</anchor>
      <arglist>(std::string imagePath)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drawImage</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>33c17e60e09f7225137859f4f85d6190</anchor>
      <arglist>(Image_ptr img, const Rect &amp;src, const Point &amp;dest)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>drawImage</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>4a32dfacefee7dac0272a9dbe1a9aa87</anchor>
      <arglist>(Image_ptr img, const Point &amp;dest)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>beginFrame</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>6388e379baeb2fba58cee34dfb05424c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>endFrame</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>a4ad537a8148eb479a56941bf6e24372</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Uint32</type>
      <name>MapColor</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>9b9a76651da2d6a3e27ef75d4536840c</anchor>
      <arglist>(const Color &amp;c)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Uint32</type>
      <name>MapColor</name>
      <anchorfile>classga_1_1GraphicsAdapterSDL.html</anchorfile>
      <anchor>c65284ef6f2b377fbc129254425316b9</anchor>
      <arglist>(SDL_Surface *surface, const Color &amp;c)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ga::Rect</name>
    <filename>classga_1_1Rect.html</filename>
    <member kind="function">
      <type></type>
      <name>Rect</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>56c09ce959dd21b0cc633f580db5dd1f</anchor>
      <arglist>(int x, int y, int w, int h)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>interseca</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>b083b4270cae1cd8cc55f8492edc9313</anchor>
      <arglist>(const Rect &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>Rect</type>
      <name>interseccion</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>6686da0d35c05cd609f997e9e7676d9c</anchor>
      <arglist>(const Rect &amp;r)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_x</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>bd1d61aa976b7e7787c062c8d23a019a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_y</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>cf19d61451cc15e30593de176336d031</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_w</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>b721ca9996f1c9c27b330dc906cedab8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>_h</name>
      <anchorfile>classga_1_1Rect.html</anchorfile>
      <anchor>175309309dc08eaab3343431b6a5c323</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>dev/cliente1/</name>
    <path>/home/alejo/dev/cliente1/</path>
    <filename>dir_5a18efa8dbc397b89c75d3c35d2af27b.html</filename>
    <dir>dev/cliente1/trunk/</dir>
  </compound>
  <compound kind="dir">
    <name>dev/cliente1/trunk/debug/</name>
    <path>/home/alejo/dev/cliente1/trunk/debug/</path>
    <filename>dir_c22ac5bfbbc44690a7210c858a36fb30.html</filename>
    <file>config.h</file>
  </compound>
  <compound kind="dir">
    <name>dev/</name>
    <path>/home/alejo/dev/</path>
    <filename>dir_bc3a21583cdbb8c06140f81a1e1f0634.html</filename>
    <dir>dev/cliente1/</dir>
  </compound>
  <compound kind="dir">
    <name>dev/cliente1/trunk/src/</name>
    <path>/home/alejo/dev/cliente1/trunk/src/</path>
    <filename>dir_32c9c3b78adfe294394b76af22dc73cf.html</filename>
    <file>aomap.cpp</file>
    <file>aomap.h</file>
    <file>class_types.h</file>
    <file>cliente1.cpp</file>
    <file>clienteargentum.cpp</file>
    <file>clienteargentum.h</file>
    <file>color.h</file>
    <file>file_types.h</file>
    <file>graphicsadapter.cpp</file>
    <file>graphicsadapter.h</file>
    <file>graphicsadaptersdl.cpp</file>
    <file>graphicsadaptersdl.h</file>
    <file>grhdata.cpp</file>
    <file>grhdata.h</file>
    <file>grhmanager.cpp</file>
    <file>grhmanager.h</file>
    <file>imagemanager.cpp</file>
    <file>imagemanager.h</file>
    <file>linked_ptr.h</file>
    <file>rect.cpp</file>
    <file>rect.h</file>
    <file>rendererengine.cpp</file>
    <file>rendererengine.h</file>
    <file>rendererenginesdl.cpp</file>
    <file>rendererenginesdl.h</file>
  </compound>
  <compound kind="dir">
    <name>dev/cliente1/trunk/</name>
    <path>/home/alejo/dev/cliente1/trunk/</path>
    <filename>dir_8fb6a10b1131c542224b90bd3c632dff.html</filename>
    <dir>dev/cliente1/trunk/debug/</dir>
    <dir>dev/cliente1/trunk/src/</dir>
  </compound>
</tagfile>
