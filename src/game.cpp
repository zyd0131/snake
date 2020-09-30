/*#include "game.hpp"
using namespace std;
// This part is for Board
Board::Board(int width, int height){
    this->width=width;
    this->height=height;
    mark_board = new cell *[height];
    for (int i = 0; i < height; i++)
    {
        mark_board[i] = new cell[width];
        for (int j = 0; j < width; j++)
        {
            mark_board[i][j] = SPACE;
        }
    }
}


void Board::set_headmarker(direction d){
    char marker = '^';
    switch (d)
    {
    case UP:
        marker = '^';
        break;
    case DOWN:
        marker = 'v';
        break;
    case LEFT:
        marker = '<';
        break;
    case RIGHT:
        marker = '>';
        break;
    }
    headmarker = marker;
}

void Board::mark(int x, int y, cell c){
    mark_board[x][y] = c;
}

void Board::unmark(int x, int y){
    int mark_x = x%height;
    int mark_y = y%width;
    if (mark_x<0)
    {
        mark_x += height;
    }
    if(mark_y<0){
        mark_y += width;
    }
    mark_board[mark_x][mark_y] = SPACE;
}

void Board::print_board(int head_x,int head_y){
    system("clear");
    for (int i = 0; i < height; i++)
    {
        // print_line1();
        print_line2(i,head_x,head_y);
    }
}

void Board::print_line1(){
    for (int i = 0; i < width*2+1; i++)
    {
        cout<<'-';
    }
    cout<<endl;
}

void Board::print_line2(int row_line,int head_x,int head_y){
    
    head_x = ((head_x%height)+height)%height;
    head_y = ((head_y%width)+width)%width;
    for (int i = 0; i < width; i++)
    {
        cout<<'|';
        if (mark_board[row_line][i]==SNAKE)
        {
            if (head_x==row_line&&head_y==i)
            {
                cout<<headmarker;
                continue;
            }
            
            cout<<marker;
        }else if (mark_board[row_line][i]==STAR)
        {
            cout<<'o';
        }else
        {
            cout<<" ";
        }
    }
    cout<<"|"<<endl;
}

cell Board::getCell(int x, int y){
    int mark_x = x%height;
    int mark_y = y%width;
    if (mark_x<0)
    {
        mark_x += height;
    }
    if(mark_y<0){
        mark_y += width;
    }
    return mark_board[mark_x][mark_y];
}


bool Board::check_filled(int snake_length){
    if(block_num+snake_length==width*height ){
        return true;
    }
    return false;
}

void Board::mark_snake(int x, int y){
    int mark_x = x%height;
    int mark_y = y%width;
    if (mark_x<0)
    {
        mark_x += height;
    }
    if(mark_y<0){
        mark_y += width;
    }
    mark(mark_x,mark_y,SNAKE);

}


void Board::random_star(int snake_length){
    int max = width*height - snake_length-star_num-block_num;
    if(max==0){
        return;
    }
    int order = rand()%max;
    int space_count = 0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (mark_board[i][j]==SPACE)
            {
                space_count +=1;
            }

            if (space_count-1==order)
            {
                mark(i,j,STAR);
                star_num++;
                return;
            }
            
               
        }
    }
    
    
    
}

// This part is for Snake

Snake::Snake(int x,int y,direction d){
    head  = new Body(x,y);
    tail  = new Body(x,y);
    tail->next=head;
    length = 1;
    head_direction = d;
}

Body *Snake::get_next_pos(){
    int x=head->x;
    int y = head->y;
    switch (head_direction)
    {
    case UP:
        x=x-1;
        break;
    case DOWN:
        x=x+1;
        break;
    case LEFT:
        y=y-1;
        break;
    case RIGHT:
        y=y+1;
        break;
    }
    return new Body(x,y);
}

void Snake::move(Body &next_pos){
    if (length==1)
    {
        head->x = next_pos.x;
        head->y = next_pos.y;
        tail->x = next_pos.x;
        tail->y = next_pos.y;
        return;
    }
    
    head->next = &next_pos;
    head = &next_pos;
    Body *temp = tail;
    tail = tail->next;
    delete temp;
}

void Snake::grow(Body &next_pos){
    if (length==1)
    {
        length = 2;
        head->x = next_pos.x;
        head->y = next_pos.y;
        return;
    }
    
    length ++;
    head->next = &next_pos;
    head = &next_pos;
}

void Snake::set_direction(direction d){
    this->head_direction = d;
}

// This part is for Game

Game::Game(int width, int height, int x, int y){
    this->snake = new Snake(x,y,DOWN);
    this->board = new Board(width,height);
}

int Game::scanKeyboard()
{
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0,&stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0,&stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new_settings);
    
    in = getchar();
    
    tcsetattr(0,TCSANOW,&stored_settings);
    return in;
}



void* Game::readInput(void* args)
{   
    char key;
    // sleep(3);
    while (true)
    {
        key = (char)scanKeyboard();
        switch (key)
        {
        case 'w':
            if(last_head_d!=DOWN)
                head_d = UP;
            break;
        case 's':
            if(last_head_d!=UP)
                head_d = DOWN;  
            break;
        case 'a':
            if(last_head_d!=RIGHT)
                head_d = LEFT;
            break;
        case 'd':
            if(last_head_d!=LEFT)
                head_d = RIGHT;
            break;
        default:
            break;
        }
        // head_d = RIGHT;
    }
    
    return 0;
}

void Game::run(){
    direction input;
    state game_state;
    pthread_t tid;
    head_d = UP;
    int ret = pthread_create(&tid, NULL, readInput, NULL);
    while (true)
    {
        // input = get_input_by_keyboard();
        last_head_d = head_d;
        game_state = step(head_d);
        settle(game_state);
        usleep(300000);
    }
}

state Game::step(direction d){
    snake->set_direction(d);
    Body *next_head = snake->get_next_pos(); 
    cell next_cell= board->getCell(next_head->x,next_head->y);
    if (next_cell==SNAKE||next_cell==BLOCK)
    {
        return FAIL;
    }
    if(board->check_filled(snake->length))
    {
        return WIN;
    }
    if (next_cell == STAR)
    {
        snake->grow(*next_head);
        board->mark_snake(snake->head->x,snake->head->y);
        board->random_star(snake->length);
    }
    if (next_cell == SPACE)
    {
        board->unmark(snake->tail->x,snake->tail->y);
        snake->move(*next_head);
        board->mark_snake(snake->head->x,snake->head->y);
    }


    return CONTINUE;
}


void Game::settle(state game_state){
    switch (game_state)
    {

    case WIN:
        win();
        break;
    case FAIL:
        fail();
        break;
    default:
        board->set_headmarker(head_d);
        board->print_board(snake->head->x,snake->head->y);
        
        break;
    }
}

void Game::win(){
    cout<<"win"<<endl;
    exit(0);
}



void Game::fail(){
    cout<<"fail"<<endl;
    exit(0);
}


direction Game::get_input_by_keyboard(){
    char input;
    cin>>input;
    switch (input)
    {
    case 'w':
        return UP;
        break;
    case 's':
        return DOWN;
        break;
    case 'a':
        return LEFT;
        break;
    case 'd':
        return RIGHT;
        break;
    default:
        cout<<"Unknown Input!!!"<<endl;
        return UP;
        break;
    }
}*/