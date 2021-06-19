#include "FilePicker.h"
#include "Editor.h"
int main()
{
    using namespace sf;
    using namespace std;
    RenderWindow window(VideoMode(1366, 768), "title", DefaultWindowMode);
    Font font;
    if(!font.loadFromFile("consola.ttf"))
    {
        std::cout << "Error while loading font.";
        return 1;
    }

    Text garbage("Select a file to open in the dialog box", font);
    garbage.setPosition(
        window.getSize().x / 2 - garbage.getGlobalBounds().width/2,
        window.getSize().y / 2 - garbage.getGlobalBounds().height/2
    );
    window.draw(garbage);
    window.display();

    FilePicker filePicker("C:/", &font);
    string path = filePicker.loop();

    if (path == "") return 0;

    Editor editor(&window, &font, path);
    editor.loop();
    return 0;
}
