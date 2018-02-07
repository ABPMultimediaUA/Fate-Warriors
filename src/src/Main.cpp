#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Movie.hpp>

const float t_min_IA=(1000/15);

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFE Movie Player");
    sfe::Movie movie;

    if (!movie.OpenFromFile("t_video6023841290775429900.mp4"))
        return 1;

    movie.ResizeToFrame(0, 0, 640, 480);
    movie.Play();

    while (window.IsOpened())
    {
        sf::Event ev;
        while (window.GetEvent(ev))
        {
            if (ev.Type == sf::Event::Closed)
                window.Close();
        }

        window.Clear();
        window.Draw(movie);
        window.Display();
    }

    return 0;
}
