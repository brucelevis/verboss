#include "GameDirector.hpp"
#include "Bind2Lua.hpp"

GameDirector* GameDirector::TGUI_GuiWrapper::s_gameDirector = nullptr;

GameDirector::GameDirector() :
        m_scriptManager(nullptr),
        m_fileSystem(nullptr)
{
    TGUI_GuiWrapper::s_gameDirector = this;
}

void GameDirector::run()
{
    m_bind2Lua();
    m_scriptManager->doFile("main.lua");

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_app->isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > m_timePerFrame)
        {
            timeSinceLastUpdate -= m_timePerFrame;
            m_app->event();
            m_app->update(m_timePerFrame);
        }

        m_app->render();
    }
}


void GameDirector::setApp(Application& app)
{
    m_app = &app;
}


void GameDirector::timePerFrame(sf::Time t)
{
    m_timePerFrame = t;
}

SceneManager& GameDirector::scenes()
{
    return m_app->scenes();
}

sf::Time GameDirector::timePerFrame() const
{
    return m_timePerFrame;
}

void GameDirector::outputError(const std::string& message)
{
    //m_app->m_window.create(sf::VideoMode(800, 600), "Error!");

    /*TODO nice error GUI**/
}

void GameDirector::m_bind2Lua()
{
    bind2lua::scriptManager(m_scriptManager);
    bind2lua::gameDirector(this);
    bind2lua::sceneManager();
    bind2lua::fileSystem(m_fileSystem);
    bind2lua::resourceManager(&m_app->resourceManager());
    bind2lua::application(m_app);
    bind2lua::entity();
    bind2lua::gui();
}

void GameDirector::setScriptManager(ScriptManager& sm)
{
    m_scriptManager = &sm;
}

void GameDirector::setFileSystem(FileSystem& fs)
{
    m_fileSystem = &fs;
}


void GameDirector::DEBUGrun()
{
    //m_bind2Lua();

    namespace ex = entityx;

    sf::RenderWindow& window = m_app->window();
    /*//LuaConsole console(window, *m_app->resourceManager().load <sf::Font> ("font", thor::Resources::fromFile <sf::Font> ("assets/font.ttf")), m_app->scenes().getScriptManager());
    ex::Entity entity = m_app->entities.create();


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            console.handleEvent(event);
        }

        m_app->systems.update <RenderSystem> (16);

        console.update(sf::seconds(1.f / 60.f));
        window.clear();
        console.render();
        window.display();
    }*/
}