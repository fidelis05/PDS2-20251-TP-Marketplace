#include <ncurses.h>
#include <vector>
#include <string>
#include <algorithm> // Required for std::transform and std::string::find
#include <cstdlib>   // Required for system()
#include <cstring>

// Mock data for products
struct Product
{
    std::string name;
    double price;
};

std::vector<Product> getMockProducts()
{
    return {
        {"Laptop", 1200.99},
        {"Mouse", 25.50},
        {"Keyboard", 75.00},
        {"Monitor", 300.20},
        {"Webcam", 50.00}};
}

// Function to filter products based on a search term
std::vector<Product> filterProducts(const std::vector<Product> &allProducts, const std::string &searchTerm)
{
    if (searchTerm.empty())
    {
        return allProducts;
    }
    std::vector<Product> filtered;
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    for (const auto &product : allProducts)
    {
        std::string lowerProductName = product.name;
        std::transform(lowerProductName.begin(), lowerProductName.end(), lowerProductName.begin(), ::tolower);
        if (lowerProductName.find(lowerSearchTerm) != std::string::npos)
        {
            filtered.push_back(product);
        }
    }
    return filtered;
}

void draw_profile_info(WINDOW *win, const std::string &userName, const std::string &userEmail, int ordersCount)
{
    werase(win);
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wattron(win, A_BOLD);
    mvwprintw(win, 0, 2, " Perfil ");
    wattroff(win, A_BOLD);
    int info_start_y = 3;
    mvwprintw(win, info_start_y, 2, "Nome: %s", userName.c_str());
    mvwprintw(win, info_start_y + 1, 2, "Email: %s", userEmail.c_str());
    mvwprintw(win, info_start_y + 2, 2, "Pedidos: %d", ordersCount);
}

void draw_product_list(WINDOW *win, const std::vector<Product> &displayedProducts, int highlight, const std::string &searchTerm, bool searching, const std::vector<Product> &allProducts)
{
    werase(win);
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);
    wattron(win, A_BOLD);
    mvwprintw(win, 0, 2, " Marketplace ");
    wattroff(win, A_BOLD);

    mvwprintw(win, 2, 2, "Pesquisa: %s", searchTerm.c_str());

    if (displayedProducts.empty() && !searchTerm.empty())
    {
        mvwprintw(win, 4, 2, "No products match your search.");
    }
    else if (displayedProducts.empty() && searchTerm.empty() && !allProducts.empty())
    {
        mvwprintw(win, 4, 2, "No products available.");
    }

    int product_win_width = getmaxx(win);
    for (int i = 0; i < displayedProducts.size(); ++i)
    {
        if (i == highlight)
        {
            wattron(win, A_REVERSE);
        }
        std::string product_line = displayedProducts[i].name + " - $" + std::to_string(displayedProducts[i].price).substr(0, std::to_string(displayedProducts[i].price).find(".") + 3);
        mvwprintw(win, i + 4, 2, "%.*s", product_win_width - 4, product_line.c_str());
        if (i == highlight)
        {
            wattroff(win, A_REVERSE);
        }
    }

    if (searching)
    {
        mvwprintw(win, LINES - 3, 2, "Digite para pesquisar.");
        mvwprintw(win, LINES - 2, 2, "`Esc` - limpa pesquisa. `q` para sair.");
    }
    else
    {
        mvwprintw(win, LINES - 3, 2, "Setas para navegar. Enter para selecionar.");
        mvwprintw(win, LINES - 2, 2, "`/` para pesquisar. `q` para sair.");
    }
}

void draw_product_details(WINDOW *win, const Product &product)
{
    werase(win);
    wbkgd(win, COLOR_PAIR(1));
    box(win, 0, 0);

    wattron(win, A_BOLD);
    std::string title = " " + product.name + " ";
    mvwprintw(win, 0, 2, "%.*s", getmaxx(win) - 4, title.c_str());
    wattroff(win, A_BOLD);

    mvwprintw(win, 2, 2, "Nome: %s", product.name.c_str());
    mvwprintw(win, 3, 2, "Preco: $%.2f", product.price);
    mvwprintw(win, 5, 2, "Pressione qualquer tecla para voltar.");
}

void show_product_details_view(
    const Product &selectedProduct,
    const std::string &userName, const std::string &userEmail, int ordersCount,
    const std::vector<Product> &displayedProducts, int highlight, const std::string &searchTerm, bool searching,
    const std::vector<Product> &allProducts)
{
    clear();
    refresh();

    int profile_w = COLS / 4;
    int product_w = COLS / 3;
    int details_w = COLS - profile_w - product_w;

    WINDOW *profile_win = newwin(LINES, profile_w, 0, 0);
    WINDOW *product_win = newwin(LINES, product_w, 0, profile_w);
    WINDOW *details_win = newwin(LINES, details_w, 0, profile_w + product_w);
    keypad(details_win, TRUE);

    draw_profile_info(profile_win, userName, userEmail, ordersCount);
    draw_product_list(product_win, displayedProducts, highlight, searchTerm, searching, allProducts);
    draw_product_details(details_win, selectedProduct);

    wrefresh(profile_win);
    wrefresh(product_win);
    wrefresh(details_win);

    wgetch(details_win);

    delwin(profile_win);
    delwin(product_win);
    delwin(details_win);

    clear();
    refresh();
}

// Function to display login screen and handle credentials
bool show_login_screen()
{
    WINDOW *login_win = newwin(10, 40, (LINES - 10) / 2, (COLS - 40) / 2);
    keypad(login_win, TRUE);
    wbkgd(login_win, COLOR_PAIR(1));
    box(login_win, 0, 0);

    mvwprintw(login_win, 1, (40 - 5) / 2, "LOGIN");

    char username_c[21] = {0};
    char password_c[21] = {0};
    int user_len = 0;
    int pass_len = 0;

    enum class State
    {
        USERNAME,
        PASSWORD,
        DONE
    };
    State state = State::USERNAME;

    mvwprintw(login_win, 3, 2, "Username: ");
    mvwprintw(login_win, 4, 2, "Password: ");
    wmove(login_win, 3, 12); // Start at username field
    wrefresh(login_win);

    int ch;
    while (state != State::DONE)
    {
        ch = wgetch(login_win);

        if (ch == KEY_RESIZE)
        {
            clear();
            refresh();
            mvwin(login_win, (LINES - 10) / 2, (COLS - 40) / 2);
            werase(login_win);
            box(login_win, 0, 0);
            mvwprintw(login_win, 1, (40 - 5) / 2, "LOGIN");
            mvwprintw(login_win, 3, 2, "Username: %s", username_c);
            std::string pass_mask(pass_len, '*');
            mvwprintw(login_win, 4, 2, "Password: %s", pass_mask.c_str());
            if (state == State::USERNAME)
            {
                wmove(login_win, 3, 12 + user_len);
            }
            else
            {
                wmove(login_win, 4, 12 + pass_len);
            }
            wrefresh(login_win);
            continue;
        }

        switch (state)
        {
        case State::USERNAME:
            if (ch == '\n')
            {
                state = State::PASSWORD;
                wmove(login_win, 4, 12);
            }
            else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
            {
                if (user_len > 0)
                {
                    user_len--;
                    username_c[user_len] = '\0';
                    mvwaddch(login_win, 3, 12 + user_len, ' ');
                    wmove(login_win, 3, 12 + user_len);
                }
            }
            else if (isprint(ch) && user_len < 20)
            {
                username_c[user_len++] = ch;
                waddch(login_win, ch);
            }
            break;
        case State::PASSWORD:
            if (ch == '\n')
            {
                state = State::DONE;
            }
            else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
            {
                if (pass_len > 0)
                {
                    pass_len--;
                    password_c[pass_len] = '\0';
                    mvwaddch(login_win, 4, 12 + pass_len, ' ');
                    wmove(login_win, 4, 12 + pass_len);
                }
            }
            else if (isprint(ch) && pass_len < 20)
            {
                password_c[pass_len++] = ch;
                waddch(login_win, '*');
            }
            break;
        case State::DONE:
            // Should not happen
            break;
        }
        wrefresh(login_win);
    }

    // Hardcoded credentials for demonstration
    if (strcmp(username_c, "user") == 0 && strcmp(password_c, "pass") == 0)
    {
        delwin(login_win);
        return true;
    }
    else
    {
        mvwprintw(login_win, 6, 2, "Invalid credentials. Press any key.");
        wrefresh(login_win);
        wgetch(login_win);
        delwin(login_win);
        return false;
    }
}

void draw_borders(WINDOW *win)
{
    box(win, 0, 0);
    wrefresh(win);
}

int main()
{
    initscr();                              // Initialize ncurses
    noecho();                               // Don't echo key presses
    cbreak();                               // Line buffering disabled, pass on everything
    start_color();                          // Enable color
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Define a color pair for borders/titles
    init_pair(3, COLOR_BLACK, COLOR_BLACK); // Color for image text

    // Show login screen first
    if (!show_login_screen())
    {
        endwin();
        return 0;
    }
    clear();   // Clear the screen after login
    refresh(); // Refresh to show the cleared screen

    int profile_win_width = COLS / 4;
    int product_win_width = COLS - profile_win_width;

    WINDOW *profile_win = newwin(LINES, profile_win_width, 0, 0);
    WINDOW *product_win = newwin(LINES, product_win_width, 0, profile_win_width);

    keypad(product_win, TRUE); // Enable function keys for product window

    std::vector<Product> allProducts = getMockProducts();
    std::vector<Product> displayedProducts = allProducts;
    std::string searchTerm = "";
    int highlight = 0;
    int choice = 0;
    int c;
    bool searching = false;

    // Mock profile data
    std::string userName = "User123";
    std::string userEmail = "user123@example.com";
    int ordersCount = 5;

    while (true)
    {
        draw_profile_info(profile_win, userName, userEmail, ordersCount);
        draw_product_list(product_win, displayedProducts, highlight, searchTerm, searching, allProducts);

        wrefresh(profile_win);
        wrefresh(product_win);

        wmove(product_win, 2, 12 + searchTerm.length());

        c = wgetch(product_win); // Get input from the product window

        if (searching)
        {
            if (c == 10)
            { // Enter key - finish searching
                searching = false;
                if (highlight >= displayedProducts.size() && !displayedProducts.empty())
                {
                    highlight = displayedProducts.size() - 1;
                }
                else if (displayedProducts.empty())
                {
                    highlight = 0;
                }
            }
            else if (c == 27)
            { // Escape key - clear search
                searchTerm = "";
                displayedProducts = filterProducts(allProducts, searchTerm);
                highlight = 0;
                searching = false;
            }
            else if (c == KEY_BACKSPACE || c == 127 || c == 8)
            {
                if (!searchTerm.empty())
                {
                    searchTerm.pop_back();
                    displayedProducts = filterProducts(allProducts, searchTerm);
                    highlight = 0;
                }
            }
            else if (isprint(c))
            {
                searchTerm += c;
                displayedProducts = filterProducts(allProducts, searchTerm);
                highlight = 0;
            }
        }
        else
        {
            switch (c)
            {
            case KEY_UP:
                if (!displayedProducts.empty())
                {
                    if (highlight == 0)
                    {
                        highlight = displayedProducts.size() - 1;
                    }
                    else
                    {
                        highlight--;
                    }
                }
                break;
            case KEY_DOWN:
                if (!displayedProducts.empty())
                {
                    if (highlight == displayedProducts.size() - 1)
                    {
                        highlight = 0;
                    }
                    else
                    {
                        highlight++;
                    }
                }
                break;
            case 10: // Enter key
                if (!displayedProducts.empty() && highlight < displayedProducts.size())
                {
                    choice = highlight;
                    show_product_details_view(
                        displayedProducts[choice],
                        userName, userEmail, ordersCount,
                        displayedProducts, highlight, searchTerm, searching,
                        allProducts);
                    touchwin(stdscr);
                    refresh();
                }
                break;
            case '/':
                searching = true;
                break;
            case 'q':
            case 'Q':
                delwin(product_win);
                delwin(profile_win);
                endwin();
                return 0;
            }
        }
    }

    delwin(product_win);
    delwin(profile_win);
    endwin();
    return 0;
}
