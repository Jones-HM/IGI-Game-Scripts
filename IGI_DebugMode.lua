--Project I.G.I DebugMode. Enables DebugMode in IGI must be execute in CheatEngine Scripts.
--Written by IGI-ResearchDevs - HM.

--Read/Write Memory functions.
function WriteMem(address,value)
writePointer(address,value)
end

function ReadMem(address)
value = readPointer(address)
return value
end

function EnableAddress(address)
writePointer(address,1)
end

function DisableAddress(address)
writePointer(address,0)
end

--Main runGameLoop
DBG_ENABLE = 0x005BDC1C
DBG_ALLOC = 0x00A5EA75
DBG_ADDR = 0x005C8BF4
DBG_PLAYER_INFO = 0x0056DF94
DBG_FONT = 0x0054D958
DBG_FONT_BIG = "LOCAL:computer/font1.fnt"
DBG_FONT_DEBUG = "LOCAL:debug.fnt"

WriteMem(DBG_ALLOC,DBG_ADDR)
writeString(DBG_FONT,DBG_FONT_BIG)
WriteMem(DBG_FONT+24,0x0)

EnableAddress(DBG_ENABLE)
EnableAddress(DBG_PLAYER_INFO)
