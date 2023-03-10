// Online C++ compiler to run C++ program online
#include<bits/stdc++.h>
using namespace std;

static int prod_id;

class Product
{
    public:
        int product_id;
        string product_name;
        string description;
        float price;
        int quantity_in_stock;
    
    Product(int id,string name,string desc,float pr,int q)
    {
        product_id = id;
        product_name = name;
        description = desc;
        price = pr;
        quantity_in_stock = q;
    }
    
    float get_total_price(int quantity)
    {
        if(quantity>quantity_in_stock){
            return -1;
        }
        else 
        {
            return (quantity*price);
        }
    }
};


 class ProductCatalog
{
  public:
    map<int,Product> products;  
    
    
    ProductCatalog()
    {
        products = {};
    }
    
    void add_product(string name,string description,float price,int quantity)
    {
        
        
        Product p(prod_id,name,description,price,quantity);
        products.insert(pair<int,Product>(prod_id,p));
        cout<<"Product have been successfully added\n";
        prod_id++;
        
    }
    
    void load_stock(int product_id,int quantity)
    {
        int flag=0;
        for (auto products_it = products.begin(); products_it != products.end(); ++products_it) 
        {   
            if(products_it->first==product_id)
            {
                cout<<"Product present\n";
                flag=1;
                products_it->second.quantity_in_stock+=quantity;
                break;
            }
            
        }
        
        if(flag==0)
        {
            cout<<"Prouct not found enter correct product id\n";
            return;
        }
    }
    Product search_product(int product_id)
    {
        int flag=0;
        for (auto products_it = products.begin(); products_it != products.end(); ++products_it) 
        {   
            if(products_it->first==product_id)
            {
                flag=1;
                cout<<"Product present\n";
                return products_it->second;
            }
            
        }
        
        if(flag==0)
        {
            cout<<"Prouct not found enter correct product id\n";
            
        }
        
    }
    
    void print_catalogue()
    {
        for (auto products_it = products.begin(); products_it != products.end(); ++products_it) 
        {   
            cout<<"Product Id : "<<products_it->second.product_id<<"\t";
            cout<<"Product Name : "<<products_it->second.product_name<<"\t";
            cout<<"Product Price : "<<products_it->second.price<<"\t";
            cout<<"Product Quantity : "<<products_it->second.quantity_in_stock;
            cout<<"\n";
        }
        cout<<"\n";
    }
};
class Cart
{
    public:
        // map for  key is product_id and value is quantity
         map<int, int> cart_items;  
         
         map<int,int>::iterator it;
        // constructor for initilise empty dict
        Cart()
        {
            cart_items = {};
            
        }
        void add_to_cart(int product_id,int quantity)
        {
            int flag=0;
            for (it = cart_items.begin(); it != cart_items.end(); ++it) {
              if(it->first == product_id){
                  flag = 1;
                  it->second += quantity;
              }
           }
           
           
           if(flag==0){
               cart_items[product_id] = quantity;
               cout<<"Cart item added in cart function\n";
           }
        }
        
        void remove_from_cart(int product_id,int quantity)
        {
           int flag=0;
            for (it = cart_items.begin(); it != cart_items.end(); ++it) {
              
              if(it->first==product_id){
                  flag=1;
                  if(it->second <= quantity){
                      cart_items.erase(it->first);
                  }
                  else{
                      cart_items[it->first]-=quantity;
                  }
              }
           }
           
           if(flag==0){
               cout<<"Product is not present in the cart"<<endl;
               return;
           } 
        }
        
        float get_cart_total(map<int,Product> product_list)
        {
            int flag=0;
            float total_price=0.0;
            for(auto prod_it=product_list.begin();prod_it!=product_list.end();++prod_it)
            {
                    for (it = cart_items.begin(); it != cart_items.end(); ++it) {
                        
                        if(prod_it->first==it->first)
                        {
                            // total_price += product_list[it->first].get_total_price(it->second);
                            flag=1;
                            total_price += prod_it->second.get_total_price(it->second);
                        }
                    
                    
                }
            }
          if(flag==0){
              cout<<"Cart is empty"<<endl;
               
          } 
           return total_price;
            
        }
        void clear_cart()
        {
            cart_items.clear();
            cout<<"Cart has been empty"<<endl;
        }
};

 class Customer
{
  public:
    int customer_id;
    string  name;
    string email;
    string address;
    float bank_balance;
    Cart cart_cust;
    
    Customer(int id,string na,string em,string add,float bal)
    {
        customer_id = id;
        name = na;
        email = em;
        address = add;
        bank_balance = bal;
        // cart_cust = c;
    }
    void add_to_cart_customer(int product_id,int quantity){
        cart_cust.add_to_cart(product_id,quantity);
        cout<<"Product added";
    }
    
    void remove_from_cart_customer(int product_id,int quantity){
        cart_cust.remove_from_cart(product_id,quantity);
    }
    
    float get_cart_total_customer(map<int, Product> prod_list){
        return cart_cust.get_cart_total(prod_list);
    }   

    void print_cart_items(ProductCatalog prod_list)
    {
        cout<<"Cart items\n";
        cout<<"Cart single"<<cart_cust.cart_items[0];
        for(auto cart_it = cart_cust.cart_items.begin();cart_it != cart_cust.cart_items.end(); ++cart_it )
        {
                        Product p = prod_list.search_product(cart_it->first);

                        
                        cout<<"Product Name : "<<p.product_name<<"\t";
                        cout<<"Product Price : "<<p.price<<"\t";
                        cout<<"Product Quantity : "<<cart_it->second;
                        cout<<"\n";
        }
    }

    
    bool checkout(map<int,Product> prod_list)
    {
        float total_price =  cart_cust.get_cart_total(prod_list);
        cout<<"Bill amount is "<<total_price;
        if(total_price > bank_balance){
            cout<<"bank balance is insufficient"<<endl;
            return false;
        }
        else{
            cout<<"to pay the bill please press 1"<<endl;
            int ch;
            cin>>ch;
            if(ch==1){
                bank_balance -= total_price;
                return true;
            }
            else
            {
                cout<<"Transaction has been canceled"<<endl;
                return false;
            }
        }
        return false;
    }
};

int main() {
    // Write C++ code here
    ProductCatalog prod_list;
    cout<<"Enter customer details\n";
    string name,email,address;
    // Cart cust_cart;
    float bal=0.0;
    cout<<"ENter customer name\n";
    getline(cin,name,'/');
    cin.ignore();
    cout<<"ENter customer email\n";
    getline(cin,email,'/');
    cin.ignore();
    cout<<"Enter customer address\n";
    getline(cin,address,'/');
    cin.ignore();
    cout<<"ENter customer balance\n";
    cin>>bal;
    Customer cust_user(1,name,email,address,bal);
    

    int ch,prod_id_user,prod_qty_user;
    string prod_name,prod_desc;
    float prod_price,cart_cust_price;
    int prod_qty,flag=0;
    while(1)
    {
        cout<<"\nWelcome to Shopping mall\n";
        cout<<"1)print productcatalog\n";
        cout<<"2)Add product\n";
        cout<<"3) load stock of product\n";
        cout<<"4) add product to cart\n";
        cout<<"5) print cart\n";
        cout<<"6) checkout cart\n";
        cout<<"7) display total price of cart\n";
        cout<<"8) display Bank balance\n";
        cout<<"9) Display product details\n";
        cout<<"10)exit\n";
        cin>>ch;
        switch(ch)
        {
            case 1:
                    prod_list.print_catalogue();
                    break;
            case 2:
                    
                    cout<<"Enter product name\n";
                    getline(cin,prod_name,'/');
                    cin.ignore();
                    cout<<"Enter product description\n";
                    getline(cin,prod_desc,'/');
                    cin.ignore();
                    cout<<"Enter product price\n";
                    cin>>prod_price;
                    cout<<"Enter product quantity\n";
                    cin>>prod_qty;
                    prod_list.add_product(prod_name,prod_desc,prod_price,prod_qty);
                    break;
            case 3:
                    cout<<"ENter product id\n";
                    cin>>prod_id_user;
                    cout<<"ENter product qty\n";
                    cin>>prod_qty_user;
                    prod_list.load_stock(prod_id_user,prod_qty_user);
                    break;
            case 4:
                    cout<<"ENter product id\n";
                    cin>>prod_id_user;
                    cout<<"ENter product qty\n";
                    cin>>prod_qty_user;
                    cust_user.add_to_cart_customer(prod_id_user,prod_qty_user);
                    break;
            case 5:
                    cust_user.print_cart_items(prod_list);
                    break;
            case 7: 
                     cart_cust_price = cust_user.get_cart_total_customer(prod_list.products);
                        cout<<"Final price of the cart"<<cart_cust_price;
                        break;
            case 8: cout<<"Customer balance = "<<cust_user.bank_balance;
                    break;
            case 9:
                    cout<<"Enter product id \n";
                    cin>>prod_id_user;
                    for (auto products_it = prod_list.products.begin(); products_it != prod_list.products.end(); ++products_it) 
                        {   
                            if(products_it->first==prod_id_user)
                            {
                                flag=1;
                                cout<<"Product present\n";
                                cout<<"product id ="<<products_it->second.product_id;
                                cout<<"product Name ="<<products_it->second.product_name;
                                cout<<"product Desc ="<<products_it->second.description;
                                cout<<"product Price ="<<products_it->second.price;
                                cout<<"product Stock ="<<products_it->second.quantity_in_stock;
                                break;
                            }

                            
                        }
                        if(flag==0){
                            cout<<"product not found\n";
                        }
                    break;
            default:
                    exit(1);
            case 6:
                    bool check_cart  = cust_user.checkout(prod_list.products);
                    if(check_cart==false){
                        cout<<"transaction failed\n";
                    }
                    else 
                    {
                        cout<<"transaction compelete\n";
                        
                        cust_user.cart_cust.clear_cart();
                    }
                    break;
            
            
            
            
        }
    }
    
}
