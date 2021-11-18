--[[Project I.G.I FreeCamera. Enables Free Roam Camera in IGI must be executed in CheatEngine Lua Script.
Controls:
X-Axis = Right/Left
Y-Axis = Up/Down
Z-Axis = Space/Alt
Angle/Roation = Mouse.
Recalibrate View = Backspace.
Start/Exit key = 'END'
Written by IGI-ResearchDevs - HM.--]]

--Global address.
viewport_task = 0x00497E94
viewport_addr = 0x00BCAAE0
camera_addr = 0x00684138

-- Structure of ViewPort.
viewport_x = 0x00BCAB08
viewport_y = viewport_x + 8
viewport_z = viewport_x + 16

-- Constants of ViewPort.
VIEWPORT_SIZE = 9
FLOAT_SIZE = 4

-- Deattach ViewPort of camera.
writeBytes(viewport_task, 0x90, 0x90)

-- Change Human 3rd view
writeInteger("[[[[0056E210]+08]+7CC]+14]+4F0", 3)

--Recalibrate Camera ViewPort (GameEngine stuff).
function RecalibrateViewPort()
writeFloat("[[[[0056E210]+08]+7CC]+14]+F3C",0.0)
writeFloat("[[[[0056E210]+08]+7CC]+14]+50C",3.095987082)
end

-- Main loop for Key events.
while not isKeyPressed(VK_END) do
    index = 0
    vport_x = readDouble(viewport_x)
    vport_y = readDouble(viewport_y)
    vport_z = readDouble(viewport_z)
    vport_off = 5.5 --Offset value to move this amount from Axis,

    -- This loop allows us to Move,Rotate,Zoom around FreeRoam camera.
    while index <= VIEWPORT_SIZE*FLOAT_SIZE do
        camera_prop = readFloat(camera_addr + index)
        writeFloat(viewport_addr + index, camera_prop)
        index = index + FLOAT_SIZE
    end

    -- Key event for X-Axis.
    if isKeyPressed(VK_RIGHT) then
        writeDouble(viewport_x, vport_x - vport_off)
    end

    if isKeyPressed(VK_LEFT) then
        writeDouble(viewport_x, vport_x + vport_off)
    end

    -- Key event for Y-Axis.
    if isKeyPressed(VK_UP) then
        writeDouble(viewport_y, vport_y - vport_off)
    end

    if isKeyPressed(VK_DOWN) then
        writeDouble(viewport_y, vport_y + vport_off)
    end

    -- Key event for Z-Axis.
    if isKeyPressed(VK_SPACE) then
        writeDouble(viewport_z, vport_z + vport_off)
    end

    if isKeyPressed(VK_MENU) then
        writeDouble(viewport_z, vport_z - vport_off)
    end

    -- Key event for Recalibrate view.
    if isKeyPressed(VK_BACK) then
         RecalibrateViewPort()
    end

end

-- Attach ViewPort of camera.
writeBytes(viewport_task, 0xF3, 0xA5)
-- Reset Human view.
writeInteger("[[[[0056E210]+08]+7CC]+14]+4F0", 1)
