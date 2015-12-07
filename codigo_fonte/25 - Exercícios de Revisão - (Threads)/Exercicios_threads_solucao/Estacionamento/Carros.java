public class Carros extends Thread{

	/*----------------------------------------------------------------*/
	private int id;

	/*----------------------------------------------------------------*/
	public Carros (int id){
		this.id = id;
	}
	/*----------------------------------------------------------------*/
	public void run(){

		Main.mutex.P();
		Main.cont++;
		if (Main.cont > Main.maxCarros){
			Main.total[this.id]++;
			Main.mutex.V();
			Main.sem[this.id].P();		
		}
		Main.mutex.V();

		if (this.id==0){
			 System.out.println("Professor entrando");
		}
		else if (this.id==1){
			 System.out.println("Funcionario entrando");
		} 
		else if (this.id==2){
			System.out.println("Aluno entrando");	
		}		


		try{
			this.sleep( (int) (Math.random() * 5) * 1000 );
		}catch(Exception e){
			e.printStackTrace();
		}

		Main.mutex.P();
		Main.cont--;
		if (Main.total[0] > 0){
			Main.total[0]--;
			Main.sem[0].V();
		}
		else if (Main.total[1] > 0 ){
			 Main.total[1]--;
		   	 Main.sem[1].V();
	        }
                else if (Main.total[2] > 0 ) {
	  		   Main.total[2]--;
  			   Main.sem[2].V();
		}	
		Main.mutex.V();

		/*----------------------------------------------------------------*/

	}
}
