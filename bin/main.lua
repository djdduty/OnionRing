print("Hello from Lua Global!")

frameCount = 0
frameTimer = 0

function onion.load()
    print("This lua file contains every bound input function!")
    onion.window.settitle("Lua, woohoo!")
end

function onion.update(deltatime)
    frameTimer = frameTimer + deltatime
    frameCount = frameCount + 1
    --print ("update... " .. deltatime)

    if frameTimer >= 1000 then
        print ("Fps: " .. frameCount)
        frameCount = 0
        frameTimer = 0
    end

    --if onion.input.iskeydown(32) then - Not working atm
    --if onion.mouse.isdown(0) then - Not working atm
end

function onion.draw()

end

function onion.unload()
    print("Done...")
end

function onion.keydown(key)
    if key == 27 then
        onion.quit()
    end

    if key == 32 then
        onion.window.setsize(800,600)
    end

    print("Key "..key.." down!")
end

function onion.keyup(key)
    print("Key "..key.." up!")
end

function onion.mousedown(button)
    print("Mouse "..button.." down. x:"..onion.mouse.getX().." y:"..onion.mouse.getY())
    if button == 1 then
        onion.mouse.hide()
    end
    if button == 3 then
        onion.mouse.show()
    end
end

function onion.mouseup(button)
    print("Mouse "..button.." up. x:"..onion.mouse.getX().." y:"..onion.mouse.getY())
end

function onion.mousemove(x, y)
    --print("Mouse moved to "..x..", "..y)
end
