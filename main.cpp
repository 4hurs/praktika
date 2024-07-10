#include <SFML/Graphics.hpp>
#include<ctime>

int ground = 370;

class Player {
public:
    float dx, dy; //скорость
    sf::FloatRect rect;
    bool onGround; 
    sf::Sprite sprite;
    float curFrame; //скорость анимации
    int a; 

    Player(sf::Texture& image) {
        sprite.setTexture(image);
        sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
        sprite.scale(2, 2);

        dx = dy = 0; 
        curFrame = 0;
        a = 0;
    }

    void update(float time) {
        rect.left += dx * time; //х коорд игрока
        if (!onGround)
            dy = dy + 0.0005 * time; //падение
        rect.top += dy * time; //у коорд игрока

        if (rect.left == 0) //нач положение
            rect.left = 100;
        if (rect.top == 0)
            rect.top = 370;

        onGround = false;

        if (rect.top > ground) {
            rect.top = ground;
            dy = 0;

            onGround = true;
        }
        if (dy == 0) {
            if (a == 0) { //спрайт 1 и 2
                curFrame += 0.0005;
                if (curFrame > 1 && curFrame < 1.50)
                    curFrame = 1.50;
                if (curFrame > 2)
                    curFrame -= 2;
            }

            else if (a == 1) { //спрайт 3 и 4
                if (curFrame < 2)
                    curFrame = 2;

                curFrame += 0.0015; 
                if (curFrame > 4)
                    curFrame -= 2;
            }

            else if (a == 2) //спрайт 5
                curFrame = 4;

            sprite.setTextureRect(sf::IntRect(50 * int(curFrame), 0, 50, 50));
        }

        sprite.setPosition(rect.left, rect.top); //100, 370
        dx = 0;
    }
};
 

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 500), "FISH!");

    sf::Texture F;
    F.loadFromFile("C:/Users/fawst/Desktop/pic1/floor.png");
    sf::Sprite Floor(F);
    Floor.scale(3, 1);
    Floor.setPosition(0, 450);

    sf::Texture K[7];
    sf::Sprite Kelp[7];
  
    K[0].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp1.png");
    K[1].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp2.png");
    K[2].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp3.png");
    K[3].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp33.png");
    K[4].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp4.png");
    K[5].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp5.png");
    K[6].loadFromFile("C:/Users/fawst/Desktop/pic1/kelp/kelp6.png");

    for (int i = 0; i < 7; i++) {
        Kelp[i].setTexture(K[i]);
        Kelp[i].scale(0.45, 0.45);

        if (i > 3)
            Kelp[i].setPosition(1000, 415);
        if (i <= 3)
            Kelp[i].setPosition(1000, 353);

    }

    sf::Texture Fishik;
    Fishik.loadFromFile("C:/Users/fawst/Desktop/pic1/fish_rect.png");
    Player p(Fishik);

    sf::Texture Ending;
    Ending.loadFromFile("C:/Users/fawst/Desktop/pic1/end.png");
    sf::Sprite ending(Ending);
    ending.setPosition(1000, 0);

    sf::Texture N;
    N.loadFromFile("C:/Users/fawst/Desktop/pic1/num.png");
    sf::Sprite number[3];
    float cnt[3] = { 0, 0, 0 };
    for (int i = 0; i < 3; i++) {
        number[i].setTexture(N);
        number[i].setTextureRect(sf::IntRect(0, 0, 20, 24));
        number[i].setPosition(950 - 25 * i, 10);
    }
   

    sf::Texture Again;
    Again.loadFromFile("C:/Users/fawst/Desktop/pic1/again.png");
    sf::Sprite again(Again);
    again.setPosition(1000, 0);

    sf::Clock clock;
    bool play = false;
    bool END = false;
    srand(time(NULL));
    int num = rand() % 7 + 1;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800; //скорость бега

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            if (p.onGround) {
                if (p.a < 2) {
                    p.dy = -0.4;
                    p.onGround = false;
                    p.sprite.setTextureRect(sf::IntRect(100, 0, 50, 50));
                    p.a = 1;
                }
                else if (p.a == 2) {
                    p.a = 1;
                    for (int i = 0; i < 7; i++) {
                        if (i > 3)
                            Kelp[i].setPosition(1000, 415);
                        if (i <= 3)
                            Kelp[i].setPosition(1000, 353);
                    }
                    int num = rand() % 7 + 1;
                    ending.setPosition(1000, 0);
                    again.setPosition(1000, 0);

                    END = false;
                    for (int i = 0; i < 3; i++) { //обнуление
                        cnt[i] = 0;
                        number[i].setTextureRect(sf::IntRect(0, 0, 20, 24));
                    }
                }
            }

        if (p.a == 1 && p.onGround == true)
            play = true;

        for (int i = 0; i < 7; i++)
            if (p.sprite.getGlobalBounds().intersects(Kelp[i].getGlobalBounds()))
                END = true;

        if (play) {
            Kelp[num - 1].move(-0.35 * time, 0);

            sf::Vector2f k[7];
            for (int i = 0; i < 7; i++) {
                k[i] = Kelp[i].getPosition();

                if (k[i].x < -100) {
                    if (i > 3)
                        Kelp[i].setPosition(1000, 415);
                    if (i <= 3)
                        Kelp[i].setPosition(1000, 353);
                    num = rand() % 7 + 1;
                }
            }
            cnt[0] += 0.00041 ;
            if (cnt[0] > 10) {
                cnt[0] -= 10;

                cnt[1]++;
                if (cnt[1] > 9) {
                    cnt[1] -= 10;

                    cnt[2]++;
                    if (cnt[2] > 9) {
                        cnt[2] -= 10;
                    }
                    number[2].setTextureRect(sf::IntRect(20 * int(cnt[2]), 0, 20, 24));
                }

                number[1].setTextureRect(sf::IntRect(20 * int(cnt[1]), 0, 20, 24));
            }

            number[0].setTextureRect(sf::IntRect(20 * int(cnt[0]), 0, 20, 24));
        }

        if (END) {
            p.a = 2;
            play = false;
            ending.setPosition(300, 200);
            again.setPosition(450, 250);
        }

        p.update(time);
        window.clear(sf::Color{ 207, 245, 255, 100 });
        window.draw(Floor);
        window.draw(again);
        window.draw(ending);
        for (int i = 0; i < 3; i++)
            window.draw(number[i]);
        window.draw(p.sprite);
        for (int i = 0; i < 7; i++)
            window.draw(Kelp[i]);
        window.display();
    }

    return 0;
}