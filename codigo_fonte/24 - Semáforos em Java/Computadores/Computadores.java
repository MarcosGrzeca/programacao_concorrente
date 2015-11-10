public class Computadores extends Thread{
    
    /*---------------------------------------------------------*/
    private int opcao = 0;
    private int valor = 0;
    private int id = 0;
    
    /*---------------------------------------------------------*/
    public Computadores(int id, int opcao, int valor) {
        this.id = id;
        this.opcao = opcao;
        this.valor = valor;
    }
    
    /*---------------------------------------------------------*/
    public void vende(int n){
        Main.exclusao.P();
        
        if (n > Main.quantidade)
           System.out.println("Thread " + this.id + " Quantidade insuficiente");
        else{
            Main.quantidade -= n;
            System.out.println("Thread " + this.id + " Quantidade " + Main.quantidade);
        }
              
        Main.exclusao.V();
    }
    
    /*---------------------------------------------------------*/
    public void compra(int n){
               
        Main.exclusao.P();
        Main.quantidade += n;
        System.out.println("Thread " + this.id + " Quantidade " + Main.quantidade);
        Main.exclusao.V();
    }
    
    /*---------------------------------------------------------*/
    public void consulta(){
       
       
        Main.mutex.P();
       
        if (Main.leitores == 0)
            Main.exclusao.P();
        Main.leitores++;
        Main.mutex.V();
        
        System.out.println("Thread " + this.id + " Quantidade " + Main.quantidade);
        
        Main.mutex.P();
        Main.leitores--;
        if (Main.leitores == 0)
            Main.exclusao.V();
        Main.mutex.V();
    }

    /*---------------------------------------------------------*/  
    public void run(){
        
        try{
            sleep(Math.round(Math.random()*10000));
        }catch(Exception e){}
        
        switch(this.opcao){
            case 0: consulta();
               break;
            case 1: vende(this.valor);
               break;
            case 2: compra(this.valor);   
                
        }
    }
    /*---------------------------------------------------------*/    
}
